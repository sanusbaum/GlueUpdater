#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "updater.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionAbout_Me_triggered();
    void updateSoftware();
    void displayError(QString error);

private:
    Ui::MainWindow *ui;
    Updater* m_updater;
};

#endif // MAINWINDOW_H
