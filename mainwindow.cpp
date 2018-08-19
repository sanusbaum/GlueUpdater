#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->updateButton, SIGNAL(clicked()), this, SLOT(updateSoftware()));
    connect(ui->versionBox, SIGNAL(returnPressed()), this, SLOT(updateSoftware()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_Me_triggered()
{
    QMessageBox::information(this, "About Me", "GlueUpdater was created by Spencer Nusbaum on 8/18/2018");
}

void MainWindow::updateSoftware()
{
    m_updater = new Updater();
    m_updater->setVersion(ui->versionBox->text());
    m_updater->checkForUpdates();

    connect(m_updater, SIGNAL(error(QString)), this, SLOT(displayError(QString)));
}

void MainWindow::displayError(QString error)
{
    qDebug() << "Message Received: " << error;
}
