#include "mainwindow.h"
#include <QApplication>
#include "login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Login login;
    login.exec();
    if (login.result() != QDialog::Accepted)
    {
        return -1;
    }

    MainWindow w;
    w.showMaximized();

    return a.exec();
}
