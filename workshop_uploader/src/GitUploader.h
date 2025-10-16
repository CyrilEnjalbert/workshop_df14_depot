// src/GitUploader.h

#pragma once
#include <QObject>
#include <QStringList>

class GitUploader : public QObject {
    Q_OBJECT
public:
    explicit GitUploader(QObject *parent = nullptr);
    bool pushFiles(const QStringList &paths, const QString &username, const QString &token);
};
