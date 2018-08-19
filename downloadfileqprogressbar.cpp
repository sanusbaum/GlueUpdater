#include "downloadfileqprogressbar.h"

DownloadFileQProgressBar::DownloadFileQProgressBar(QWidget* parent) : QProgressBar(parent)
{
    setMinimum(0);
    setMaximum(100);
}

void DownloadFileQProgressBar::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    setValue(bytesReceived * 100.0 / bytesTotal);
}
