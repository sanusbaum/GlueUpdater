#include "updaterdialog.h"
#include "ui_updaterdialog.h"

UpdaterDialog::UpdaterDialog(QList<DownloadFile*> downloads, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdaterDialog)
{
    ui->setupUi(this);
    m_downloads = downloads;

    QVBoxLayout* layout = new QVBoxLayout();

    m_totalNumberOfDownloads = m_totalNumberOfDownloadsCompleted = 0;
    QList<DownloadFile*>::iterator downloadsIterator = m_downloads.begin();
    for (; downloadsIterator != m_downloads.end(); downloadsIterator++, m_totalNumberOfDownloads++)
    {
        DownloadFileQProgressBar* progressBar = new DownloadFileQProgressBar(this);
        DownloadFile* downloadFile = *downloadsIterator;
        connect(downloadFile, SIGNAL(downloadProgress(qint64, qint64)), progressBar, SLOT(downloadProgress(qint64, qint64)));
        connect(downloadFile, SIGNAL(finished()), this, SLOT(finishedCalled()));
        connect(downloadFile, SIGNAL(error(QString)), this, SIGNAL(error(QString)));
        layout->addWidget(progressBar);
        downloadFile->start();
    }

    ui->scrollAreaWidgetContents->setLayout(layout);
    ui->downloadingUpdatesLabel->setText("Downloading updates (0 out of " + QString::number(m_totalNumberOfDownloads) + " updates complete)");

    connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(reject()));
}

UpdaterDialog::~UpdaterDialog()
{
    delete ui;
}

void UpdaterDialog::reject()
{
    QList<DownloadFile*>::iterator downloadsIterator = m_downloads.begin();
    for (; downloadsIterator != m_downloads.end(); downloadsIterator++)
    {
        DownloadFile* downloadFile = *downloadsIterator;
        downloadFile->stop();
        delete downloadFile;
    }
    QDialog::reject();
}

void UpdaterDialog::finishedCalled()
{
    m_totalNumberOfDownloadsCompleted++;
    ui->downloadingUpdatesLabel->setText("Downloading updates (" + QString::number(m_totalNumberOfDownloadsCompleted) + " out of " + QString::number(m_totalNumberOfDownloads) + " updates complete)");

    if (m_totalNumberOfDownloadsCompleted == m_totalNumberOfDownloads)
    {
        QMessageBox::information(this, "Updates Downloaded and Installed!", "Updates were downloaded and installed! Please exit and restart the program to continue.");
        reject();
    }
}
