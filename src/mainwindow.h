#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dbmanager.h"
#include <QString>
#include <QHash>
#include <QTreeWidgetItem>
#include <QWebEnginePage>

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

    void on_actionBill_triggered();

    void on_actionGST_Bill_triggered();

    void on_actionReport_triggered();

    void pdfPrintingFinishedSimpleBill(const QString &filePath, bool success);

    void loadFinishedSimpleBill(bool ok);

    void pdfPrintingFinishedGstBill(const QString &filePath, bool success);

    void loadFinishedGstBill(bool ok);

private:
    Ui::MainWindow *ui;
    DbManager *db;
    void fillBookingHistoryTree(void);
    void deleteAllBookingFromTree(void);
    QWebEnginePage *msimpleBillPage;
    QWebEnginePage *mgstBillPage;
};

#endif // MAINWINDOW_H
