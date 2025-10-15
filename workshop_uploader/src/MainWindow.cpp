#include "MainWindow.h"
#include "GitUploader.h"      // ajoute ceci
#include <QMimeData>
#include <QDragEnterEvent>
#include <QMessageBox>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Workshop Uploader");
    setAcceptDrops(true);
    resize(500, 300);

    label = new QLabel("Glissez vos fichiers ici pour les envoyer", this);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("font-size:18px; color:#222; border:2px dashed #888; padding:40px;");

    auto *layout = new QVBoxLayout;
    layout->addWidget(label);

    auto *central = new QWidget;
    central->setLayout(layout);
    setCentralWidget(central);

    // ---- ajoute cette ligne ici ----
    uploader = new GitUploader(this);
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent *event) {
    QStringList files;
    for (auto &url : event->mimeData()->urls())
        files << url.toLocalFile();

    bool ok = uploader->pushFiles(files);

    QString message = ok ? "Push GitHub réussi" : "Erreur push GitHub";
    QMessageBox::information(this, "Résultat", message);
}
