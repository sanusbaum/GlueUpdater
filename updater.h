#ifndef UPDATER_H
#define UPDATER_H

#include <QObject>
#include <QString>
#include <QMessageBox>
#include <QDir>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QNetworkReply>
#include "updaterdialog.h"
#include "downloadfile.h"

class Updater : public QObject
{
    Q_OBJECT

signals:
    void error(QString errorMessage);

public:
    Updater();

    void setVersion(QString versionIdentifier);
    void checkForUpdates();

private slots:
    void finishedDownloadingUpdateFile();
    void networkError(QNetworkReply::NetworkError networkError);

private:
    DownloadFile* m_downloadUpdateFile;
    QString m_versionIdentifier;
    int m_totalNumberOfDownloads;

    QString platformIdentifier();

};

#endif // UPDATER_H
