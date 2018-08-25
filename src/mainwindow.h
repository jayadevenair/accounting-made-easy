#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dbmanager.h"
#include <QString>
#include <QHash>
#include <QTreeWidgetItem>

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

    void on_action_Open_triggered();

    void on_actionDelete_triggered();

private:
    Ui::MainWindow *ui;
    DbManager *db;
    void fillBookingHistoryTree(void);
    void addNewBookingToTree(QHash <QString, QString> &newBookingCache);
    void updateBookingToTree(QTreeWidgetItem *selectedItem, QHash <QString,
                             QString> &newBookingCache);
    void deleteBookingFromTree(QTreeWidgetItem *bookingNode);
};

#endif // MAINWINDOW_H
