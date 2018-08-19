#ifndef UPDATERDIALOG_H
#define UPDATERDIALOG_H

#include <QDialog>
#include <QProgressBar>
#include <QList>
#include <QMessageBox>
#include "downloadfile.h"
#include "downloadfileqprogressbar.h"

namespace Ui {
class UpdaterDialog;
}

class UpdaterDialog : public QDialog
{
    Q_OBJECT

signals:
    void error(QString errorMessage);

public:
    explicit UpdaterDialog(QList<DownloadFile*> downloads, QWidget *parent = nullptr);
    virtual ~UpdaterDialog() override;
    void reject() override;

private slots:
    void finishedCalled();
    void canceled();

private:
    Ui::UpdaterDialog *ui;
    QList<DownloadFile*> m_downloads;
    int m_totalNumberOfDownloads;
    int m_totalNumberOfDownloadsCompleted;
};

#endif // UPDATERDIALOG_H
