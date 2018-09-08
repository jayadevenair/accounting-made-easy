#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newquotationdialogue.h"
#include "reportdialoguebox.h"
#include <QString>
#include <QDebug>
#include <QDialog>
#include <QFile>
#include <QPrinter>
#include <QWebView>

static const QString dbPath = "/home/ejayadev/mydata.db";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = new DbManager(dbPath);
    fillBookingHistoryTree();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete db;
}

void MainWindow::on_action_New_triggered()
{
    QHash <QString, QString> newBookingCache;
    NewQuotationDialogue *quot = new NewQuotationDialogue;

    quot->updateInProgress = false;
    quot->exec();
    if (quot->result() == QDialog::Accepted)
    {
        deleteAllBookingFromTree();
        fillBookingHistoryTree();
    }
}


void MainWindow::fillBookingHistoryTree(void)
{
    QList < QHash <QString, QString> > allBookings;
    QHash <QString, QString> booking;

    DbManager::getAllBookingHistory(allBookings);

    foreach(booking, allBookings)
    {
        QTreeWidgetItem *bookingNode = new QTreeWidgetItem;
        bookingNode->setText(0, booking["bookingid"]);
        bookingNode->setText(1, booking["bookingdate"]);
        bookingNode->setText(2, booking["bookingtime"]);
        bookingNode->setText(3, booking["customername"]);
        bookingNode->setText(4, booking["destinations"]);
        bookingNode->setText(5, booking["profit"]);

        ui->treeWidgetAllBooking->addTopLevelItem(bookingNode);
    }
}

void MainWindow::on_action_Open_triggered()
{
    QTreeWidgetItem *selectedItem;
    QHash <QString, QString> newBookingCache;
    NewQuotationDialogue *quot = new NewQuotationDialogue;
    qint64 bookingId;

    selectedItem = ui->treeWidgetAllBooking->selectedItems()[0];
    bookingId = selectedItem->text(0).toLongLong();

    quot->updateInProgress = true;
    quot->initQuotationDialogue(bookingId);
    quot->exec();
    if (quot->result() == QDialog::Accepted)
    {
        deleteAllBookingFromTree();
        fillBookingHistoryTree();
    }
}

void MainWindow::on_actionDelete_triggered()
{
    QTreeWidgetItem *selectedItem;
    QHash <QString, QString> newBookingCache;
    qint64 bookingId;

    selectedItem = ui->treeWidgetAllBooking->selectedItems()[0];
    bookingId = selectedItem->text(0).toLongLong();
    DbManager::deleteBookingEntry(bookingId);
    DbManager::deleteTripEntry(bookingId);
    DbManager::deleteExpenseEntry(bookingId);
    deleteAllBookingFromTree();
    fillBookingHistoryTree();
}

void MainWindow::deleteAllBookingFromTree()
{
    ui->treeWidgetAllBooking->clear();
}

void MainWindow::on_actionBill_triggered()
{
    QFile file("/home/ejayadev/work/fir/html-invoice-template/index.html");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    QString text;
    text = in.readAll();
    file.close();

    // Initialize printer and set save location
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName("/home/ejayadev/simple_bill.pdf");

    // Create webview and load html source
    QWebView webview;
    webview.setHtml(text);

    // Create PDF
    webview.print(&printer);
}

void MainWindow::on_actionGST_Bill_triggered()
{

}

void MainWindow::on_actionReport_triggered()
{
    ReportDialogueBox *report = new ReportDialogueBox;

    report->exec();
}
