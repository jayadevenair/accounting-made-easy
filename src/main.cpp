#include "mainwindow.h"
#include <QApplication>
#include "login.h"
#include "googledrive.h"
#include <QWidget>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Login login;
    login.exec();
    if (login.result() != QDialog::Accepted)
    {
        return -1;
    }

    //GoogleDrive drive;
    //drive.backup_db();

    MainWindow w;
    w.showMaximized();

    return a.exec();
}
