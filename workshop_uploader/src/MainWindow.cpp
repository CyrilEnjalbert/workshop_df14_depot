// src/MainWindow.cpp

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

    usernameEdit = new QLineEdit(this);
    usernameEdit->setPlaceholderText("GitHub Username");
    usernameEdit->setGeometry(20, 20, 200, 25);

    tokenEdit = new QLineEdit(this);
    tokenEdit->setPlaceholderText("Personal Access Token");
    tokenEdit->setEchoMode(QLineEdit::Password);
    tokenEdit->setGeometry(20, 60, 200, 25);

    pushButton = new QPushButton("Push Files", this);
    pushButton->setGeometry(20, 100, 200, 30);
    connect(pushButton, &QPushButton::clicked, this, &MainWindow::onPushClicked);

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

    QString user = usernameEdit->text();
    QString token = tokenEdit->text();

    bool ok = uploader->pushFiles(files, user, token);

    QString message = ok ? "Push GitHub réussi" : "Erreur push GitHub";
    QMessageBox::information(this, "Résultat", message);
}

void MainWindow::onPushClicked() {
    QString user = usernameEdit->text();
    QString token = tokenEdit->text();

    QStringList files; // Fill this with the files you want to push
    // Example: files << "/home/c-enjalbert/Téléchargements/file.pdf";

    bool ok = uploader->pushFiles(files, user, token);
    if (ok) {
        qDebug() << "Push succeeded";
    } else {
        qDebug() << "Push failed";
    }
}
