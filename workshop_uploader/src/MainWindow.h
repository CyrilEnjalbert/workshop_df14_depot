#pragma once
#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include "GitUploader.h" // Include the GitUploader class

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private slots:
    void onPushClicked();

private:
    QLabel *label;
    QLineEdit *usernameEdit;
    QLineEdit *tokenEdit;
    QPushButton *pushButton;
    GitUploader *uploader; // Use the GitUploader class
};