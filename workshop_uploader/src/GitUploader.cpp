#include "GitUploader.h"
#include <git2.h>
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <QFile>

GitUploader::GitUploader(QObject *parent) : QObject(parent) {
    git_libgit2_init();
}

bool GitUploader::pushFiles(const QStringList &paths) {
    git_repository *repo = nullptr;

    // Path to your repo root
    QString repoPath = "/home/c-enjalbert/Documents/EPSI/WORKSHOP/Workshop-Poudlard-2025-M2-g4/Defi14-LA-BOITE-MAGIQUE-DE-SERVERUS-ROGUE";

    QString docsPath = repoPath + "/docs";
    QDir().mkpath(docsPath);

    QStringList copiedFiles;
    for (auto &p : paths) {
        QFileInfo fi(p);
        QString destPath = docsPath + "/" + fi.fileName();

        if (QFile::exists(destPath))
            QFile::remove(destPath);

        if (QFile::copy(p, destPath)) {
            copiedFiles << destPath;
            qDebug() << "Copied file to:" << destPath;
        } else {
            qDebug() << "Failed to copy file:" << p << "->" << destPath;
            qDebug() << "Check read permissions and valid path.";
            return false;  // ← no repo cleanup needed here
        }
    }

    // Now open the repo
    if (git_repository_open(&repo, repoPath.toUtf8().data()) != 0) {
        qDebug() << "Cannot open repository at" << repoPath;
        return false;
    }

    // 4. Open the index
    git_index *index = nullptr;
    if (git_repository_index(&index, repo) != 0) {
        qDebug() << "Cannot open repository index";
        git_repository_free(repo);
        return false;
    }

    // 5. Add copied files to index
    for (auto &p : copiedFiles) {
        QString relativePath = QDir(repoPath).relativeFilePath(p);
        if (git_index_add_bypath(index, relativePath.toUtf8().data()) != 0) {
            qDebug() << "Failed to add file to index:" << relativePath;
        } else {
            qDebug() << "Added file to index:" << relativePath;
        }
    }

    if (git_index_write(index) != 0) {
        qDebug() << "Failed to write index";
        git_index_free(index);
        git_repository_free(repo);
        return false;
    }

    // 6. Write tree
    git_oid tree_id, commit_id;
    if (git_index_write_tree(&tree_id, index) != 0) {
        qDebug() << "Failed to write tree";
        git_index_free(index);
        git_repository_free(repo);
        return false;
    }

    git_tree *tree = nullptr;
    if (git_tree_lookup(&tree, repo, &tree_id) != 0) {
        qDebug() << "Failed to lookup tree";
        git_index_free(index);
        git_repository_free(repo);
        return false;
    }

    // 7. Create signature and commit (handle first commit case)
    git_signature *sig = nullptr;
    if (git_signature_now(&sig, "WorkshopUploader", "auto@local") != 0) {
        qDebug() << "Failed to create signature";
        git_tree_free(tree);
        git_index_free(index);
        git_repository_free(repo);
        return false;
    }

    // Try to get HEAD reference (may fail if first commit)
    git_reference *headRef = nullptr;
    git_commit *parentCommit = nullptr;
    int headResult = git_repository_head(&headRef, repo);

    if (headResult == 0) {
        git_object *parentObj = nullptr;
        if (git_reference_peel(&parentObj, headRef, GIT_OBJECT_COMMIT) == 0) {
            parentCommit = (git_commit *)parentObj;
        }
    } else {
        qDebug() << "No HEAD found, repository may be empty. Creating first commit.";
    }

    const git_commit *parents[1];
    size_t parentCount = 0;
    if (parentCommit) {
        parents[0] = parentCommit;
        parentCount = 1;
    }

    if (git_commit_create(
            &commit_id,
            repo,
            "HEAD",
            sig,
            sig,
            nullptr,
            "Auto upload",
            tree,
            parentCount,
            parents) != 0) {
        qDebug() << "Failed to create commit";
        git_signature_free(sig);
        if (parentCommit) git_commit_free(parentCommit);
        if (headRef) git_reference_free(headRef);
        git_tree_free(tree);
        git_index_free(index);
        git_repository_free(repo);
        return false;
    }

    if (parentCommit) git_commit_free(parentCommit);
    if (headRef) git_reference_free(headRef);


    // 8. Push to origin
    git_remote *remote = nullptr;
    if (git_remote_lookup(&remote, repo, "origin") != 0) {
        qDebug() << "Cannot find remote origin";
        git_signature_free(sig);
        git_tree_free(tree);
        git_index_free(index);
        git_repository_free(repo);
        return false;
    }

    if (git_remote_push(remote, nullptr, nullptr) != 0) {
        qDebug() << "Push failed";
        git_remote_free(remote);
        git_signature_free(sig);
        git_tree_free(tree);
        git_index_free(index);
        git_repository_free(repo);
        return false;
    }

    // 9. Cleanup
    git_remote_free(remote);
    git_signature_free(sig);
    git_tree_free(tree);
    git_index_free(index);
    git_repository_free(repo);

    qDebug() << "Push successful";
    return true;
}
