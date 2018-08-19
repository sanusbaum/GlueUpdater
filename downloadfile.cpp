#include "downloadfile.h"

DownloadFile::DownloadFile(QString downloadPath, QString storePath, QString installPath, bool start)
{
    m_downloadPath = downloadPath;
    m_storePath = storePath;
    m_installPath = (installPath == "") ? storePath : installPath;

    if (start)
    {
        DownloadFile::start();
    }
}

DownloadFile::~DownloadFile()
{
    emit error("download finished");

    if (m_reply->isOpen())
    {
        m_reply->close();
    }

    delete m_manager;
    if (m_file)
    {
        m_file->close();
        delete m_file;
        m_file = nullptr;
    }
}

void DownloadFile::start()
{
    emit error("download started");

    m_file = new QFile(m_storePath);
    m_file->open(QIODevice::WriteOnly);

    m_manager = new QNetworkAccessManager();
    QUrl qurl(m_downloadPath);
    m_networkRequest = new QNetworkRequest(qurl);
    m_reply = m_manager->get(*m_networkRequest);

    connect(m_reply, SIGNAL(finished()), this, SLOT(downloadFinished()));
    connect(m_reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(mdownloadProgress(qint64, qint64)));
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SIGNAL(error(QNetworkReply::NetworkError)));
}

void DownloadFile::stop()
{
    emit error("download stopped");
    m_reply->abort();
}

void DownloadFile::downloadFinished()
{
    if (m_bytesReceived == m_bytestotal)
    {
        emit error("download file complete");
        m_reply->close();

        if (m_storePath != m_installPath)
        {
            m_file->rename(m_installPath);
        }

        emit finished();
    }
    else
    {
        emit canceled();
    }
}

void DownloadFile::mdownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    m_bytesReceived = bytesReceived;
    m_bytestotal = bytesTotal;

    if (m_file->isOpen() && m_reply->isOpen())
    {
        m_file->write(m_reply->readAll());
    }

    emit downloadProgress(bytesReceived, bytesTotal);
}
