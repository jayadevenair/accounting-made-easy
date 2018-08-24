#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dbmanager.h"
#include <QString>
#include <QHash>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_action_New_triggered();

private:
    Ui::MainWindow *ui;
    DbManager *db;
    void fillBookingHistoryTree(void);
    void addNewBookingToTree(QHash <QString, QString> &newBookingCache);
};

#endif // MAINWINDOW_H
