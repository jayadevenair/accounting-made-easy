#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newquotationdialogue.h"
#include "reportdialoguebox.h"
#include <QString>
#include <QDebug>
#include <QDialog>
#include <QFile>
#include <QPrinter>
#include <QWebEngineView>

static const QString dbPath = "/home/ejayadev/mydata.db";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = new DbManager(dbPath);
    msimpleBillPage = new QWebEnginePage;
    mgstBillPage = new QWebEnginePage;
    connect(msimpleBillPage, &QWebEnginePage::loadFinished,
            this, &MainWindow::loadFinishedSimpleBill);
    connect(msimpleBillPage, &QWebEnginePage::pdfPrintingFinished,
            this, &MainWindow::pdfPrintingFinishedSimpleBill);
    connect(mgstBillPage, &QWebEnginePage::loadFinished,
            this, &MainWindow::loadFinishedGstBill);
    connect(mgstBillPage, &QWebEnginePage::pdfPrintingFinished,
            this, &MainWindow::pdfPrintingFinishedGstBill);
    fillBookingHistoryTree();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete db;
    delete msimpleBillPage;
    delete mgstBillPage;
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

void MainWindow::loadFinishedSimpleBill(bool ok)
{
    if (!ok) {
        QTextStream(stderr)
            << tr("failed to load simple bill html") << "\n";
        return;
    }
    msimpleBillPage->printToPdf((QString)"/home/ejayadev/normal_bill.pdf");
}

void MainWindow::pdfPrintingFinishedSimpleBill(const QString &filePath, bool success)
{
    if (!success) {
        QTextStream(stderr)
            << tr("failed to print to output file '%1'").arg(filePath) << "\n";
    } else {
        QTextStream(stderr)
            << tr("successfully generated normal bill at '%1'").arg(filePath) << "\n";
    }
}

void MainWindow::loadFinishedGstBill(bool ok)
{
    if (!ok) {
        QTextStream(stderr)
            << tr("failed to load gst bill html") << "\n";
        return;
    }
    mgstBillPage->printToPdf((QString)"/home/ejayadev/gst_bill.pdf");
}

void MainWindow::pdfPrintingFinishedGstBill(const QString &filePath, bool success)
{
    if (!success) {
        QTextStream(stderr)
            << tr("failed to generate gst bill at '%1'").arg(filePath) << "\n";
    } else {
        QTextStream(stderr)
            << tr("successfully generated gst bill at '%1'").arg(filePath) << "\n";
    }
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

    msimpleBillPage->setHtml(text);
}

void MainWindow::on_actionGST_Bill_triggered()
{
    QFile file("/home/ejayadev/work/fir/html-invoice-template/index.html");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    QString text;
    text = in.readAll();
    file.close();

    mgstBillPage->setHtml(text);

}

void MainWindow::on_actionReport_triggered()
{
    ReportDialogueBox *report = new ReportDialogueBox;

    report->exec();
}
