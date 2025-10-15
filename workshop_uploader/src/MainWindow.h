#pragma once
#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include "GitUploader.h"


class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
private:
    QLabel *label;
    GitUploader *uploader;
};



