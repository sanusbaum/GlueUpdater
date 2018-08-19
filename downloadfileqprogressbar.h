#ifndef DOWNLOADFILEQPROGRESSBAR_H
#define DOWNLOADFILEQPROGRESSBAR_H

#include <QProgressBar>
#include <QString>

class DownloadFileQProgressBar : public QProgressBar
{
    Q_OBJECT

public:
    DownloadFileQProgressBar(QWidget* parent = nullptr);

public slots:
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);

};

#endif // DOWNLOADFILEQPROGRESSBAR_H
