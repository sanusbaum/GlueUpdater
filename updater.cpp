#include "updater.h"

Updater::Updater()
{
}

void Updater::setVersion(QString versionIdentifier)
{
    m_versionIdentifier = versionIdentifier;
}

void Updater::checkForUpdates()
{
    m_downloadUpdateFile = new DownloadFile("http://spencernusbaum.com/updates.php?version=" + m_versionIdentifier, "updates.json");

    connect(m_downloadUpdateFile, SIGNAL(finished()), this, SLOT(finishedDownloadingUpdateFile()));
    connect(m_downloadUpdateFile, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkError(QNetworkReply::NetworkError)));
    connect(m_downloadUpdateFile, SIGNAL(error(QString)), this, SIGNAL(error(QString)));
}

void Updater::finishedDownloadingUpdateFile()
{
    delete m_downloadUpdateFile; // closes the updates.json file
    // open updates.json into a JSON paraser
    QFile updatesFile("updates.json");
    if (updatesFile.open(QIODevice::ReadOnly))
    {
        QJsonDocument jsonDocument = QJsonDocument::fromJson(updatesFile.readAll());
        if (jsonDocument.isNull())
        {
            QMessageBox::information(nullptr, "No Updates Found", "No updates were found at this time. You should be completely up to date!");
            emit error("No updates were found");
            return;
        }

        // Updates found, prompt to install them
        QMessageBox promptToInstall;
        promptToInstall.setIcon(QMessageBox::Question);
        promptToInstall.setDefaultButton(QMessageBox::Ok);
        promptToInstall.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        promptToInstall.setInformativeText("Updates were found! Click \"OK\" to begin installing the updates.");
        promptToInstall.setText("<h3>In order to install and configure the update completely, you may need to quit the application.</h2>");

        if (promptToInstall.exec() == QMessageBox::Ok)
        {

            QJsonObject jsonUpdates = jsonDocument.object().value("updates").toObject();
            QJsonArray jsonPlatformArray = jsonUpdates.value(platformIdentifier()).toArray();

            QList<DownloadFile*> downloads;

            QJsonArray::iterator jsonIterator = jsonPlatformArray.begin();
            for (; jsonIterator != jsonPlatformArray.end(); jsonIterator++)
            {
                QJsonObject jsonUpdateObject = jsonIterator->toObject();
                if (jsonUpdateObject.value("operation") == "add")
                {
                    downloads.push_back(new DownloadFile(
                                            jsonUpdateObject.value("download-url").toString(),
                                            jsonUpdateObject.value("download-location").toString(),
                                            jsonUpdateObject.value("extract-path").toString(),
                                            false));
                }
                else if (jsonUpdateObject.value("operation") == "update")
                {
                    downloads.push_back(new DownloadFile(
                                            jsonUpdateObject.value("download-url").toString(),
                                            jsonUpdateObject.value("download-location").toString(),
                                            jsonUpdateObject.value("extract-path").toString(),
                                            false));
                }
                else if (jsonUpdateObject.value("operation") == "remove")
                {
                    QFile fileToRemove(jsonUpdateObject.value("file-location").toString());
                    fileToRemove.remove();
                }
                else if (jsonUpdateObject.value("operation") == "move")
                {
                    QFile fileToMove(jsonUpdateObject.value("file-location").toString());
                    fileToMove.rename(jsonUpdateObject.value("file-move-location").toString());
                }
                else if (jsonUpdateObject.value("operation") == "mkdir")
                {
                    QDir().mkdir(jsonUpdateObject.value("directory-location").toString());
                }
            }

            if (downloads.size() == 0)
            {
                QMessageBox::information(nullptr, "Updates Downloaded and Installed!", "Updates were configured! Please exit and restart the program to continue.");
            }
            else
            {
                UpdaterDialog updaterDialog(downloads);
                connect(&updaterDialog, SIGNAL(error(QString)), this, SIGNAL(error(QString)));
                updaterDialog.exec();
            }
        }
        else
        {
            emit error("User canceled updates");
        }
    }
    else
    {
        emit error("Unable to continue: Could not open updates.json file for reading");
    }
}

void Updater::networkError(QNetworkReply::NetworkError networkError)
{
    emit error("Network error: " + QString::number(networkError));
}

QString Updater::platformIdentifier()
{
#if defined Q_OS_WIN
    return "windows";
#elif defined Q_OS_LINUX
    return "linux";
#elif defined Q_OS_MAC
    return "osx";
#elif defined Q_OS_ANDROID
    return "android";
#elif defined Q_OS_IOS
    return "ios";
#endif
}
