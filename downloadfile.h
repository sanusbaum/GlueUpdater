#ifndef DOWNLOADFILE_H
#define DOWNLOADFILE_H

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QFile>
#include <QList>
#include <QByteArray>

class DownloadFile : public QObject
{
    Q_OBJECT

signals:
    void finished();
    void downloadProgress(qint64 bytesSent, qint64 bytesTotal);
    void error(QString error);

public:
    DownloadFile(QString downloadPath, QString storePath, QString installPath = "", bool start = true);
    ~DownloadFile();

    void start();
    void stop();

private slots:
    void downloadFinished();
    void mdownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void networkError(QNetworkReply::NetworkError error);

private:
    QNetworkAccessManager* m_manager;
    QNetworkRequest* m_networkRequest;
    QNetworkReply* m_reply;
    QList<QByteArray> m_data;
    QFile* m_file;
    QString m_downloadPath;
    QString m_storePath;
    QString m_installPath;
    qint64 m_bytesReceived;
    qint64 m_bytestotal;

};

#endif // DOWNLOADFILE_H
