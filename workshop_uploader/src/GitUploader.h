#pragma once
#include <QObject>
#include <QStringList>

class GitUploader : public QObject {
    Q_OBJECT
public:
    explicit GitUploader(QObject *parent = nullptr);   // doit exister
    bool pushFiles(const QStringList &paths);
};
