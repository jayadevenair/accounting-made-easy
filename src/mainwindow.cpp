#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "advancebooking.h"
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
    fillAccountsTree();
    fillAdvanceBookingTree();
    ui->tabWidgetTopLevel->setCurrentIndex(ADVANCE_BOOKING_TAB);
    ui->tabWidgetAdvanceBooking->setCurrentIndex(ONGOING_TRIPS);
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

    if (ui->tabWidgetTopLevel->currentIndex() == ADVANCE_BOOKING_TAB) {
        AdvanceBooking *adv = new AdvanceBooking;

        adv->updateInProgress = false;
        adv->exec();
        if (adv->result() == QDialog::Accepted)
        {
            deleteAllAdvanceBookingFromTree();
            fillAdvanceBookingTree();
        }
    } else if(ui->tabWidgetTopLevel->currentIndex() == ACCOUNTS_TAB) {
        NewQuotationDialogue *quot = new NewQuotationDialogue;

        quot->updateInProgress = false;
        quot->exec();
        if (quot->result() == QDialog::Accepted)
        {
            deleteAllBookingFromTree();
            fillAccountsTree();
        }
    }
}

void MainWindow::fillAccountsTree(void)
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
        bookingNode->setText(4, booking["mobilenumber"]);
        bookingNode->setText(5, booking["destinations"]);
        bookingNode->setText(6, booking["totalincome"]);
        bookingNode->setText(7, booking["totalexpense"]);
        bookingNode->setText(8, booking["profit"]);


        ui->treeWidgetAccounts->addTopLevelItem(bookingNode);
    }
    ui->treeWidgetAccounts->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void MainWindow::fillAdvanceBookingTree(void)
{
    QList < QHash <QString, QString> > allAdvanceBookings;
    QHash <QString, QString> booking;

    DbManager::getAllAdvanceBookingHistory(allAdvanceBookings);

    foreach(booking, allAdvanceBookings)
    {
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QTreeWidgetItem *advanceBookingNode = new QTreeWidgetItem;
        QString now;

        advanceBookingNode->setText(0, booking["bookingid"]);
        advanceBookingNode->setText(1, booking["bookingdatetime"]);
        advanceBookingNode->setText(2, booking["customername"]);
        advanceBookingNode->setText(3, booking["mobilenumber"]);
        advanceBookingNode->setText(4, booking["destinations"]);
        advanceBookingNode->setText(5, booking["departuredatetime"]);
        advanceBookingNode->setText(6, booking["arrivaldatetime"]);
        advanceBookingNode->setText(7, booking["advance"]);
        advanceBookingNode->setText(8, booking["numpassengers"]);
        advanceBookingNode->setText(9, booking["perheadamount"]);
        advanceBookingNode->setText(10, booking["totalamount"]);

        now = currentDateTime.date().toString(Qt::ISODate) + " " + currentDateTime.time().toString();
        if (now > booking["arrivaldatetime"]) {
            ui->treeWidgetPastTrips->addTopLevelItem(advanceBookingNode);
        } else if (now < booking["departuredatetime"]) {
            ui->treeWidgetUpcomingTrips->addTopLevelItem(advanceBookingNode);
        } else {
            ui->treeWidgetOngoingTrips->addTopLevelItem(advanceBookingNode);
        }
    }
    ui->treeWidgetUpcomingTrips->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->treeWidgetOngoingTrips->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->treeWidgetPastTrips->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void MainWindow::on_action_Open_triggered()
{
    QTreeWidgetItem *selectedItem;

    if (ui->tabWidgetTopLevel->currentIndex() == ADVANCE_BOOKING_TAB) {
        AdvanceBooking *adv = new AdvanceBooking;
        qint64 advanceBookingId;

        switch(ui->tabWidgetAdvanceBooking->currentIndex()) {
            case UPCOMING_TRIPS:
                selectedItem = ui->treeWidgetUpcomingTrips->selectedItems()[0];
                break;

            case ONGOING_TRIPS:
                selectedItem = ui->treeWidgetOngoingTrips->selectedItems()[0];
                break;

            case PAST_TRIPS:
                selectedItem = ui->treeWidgetPastTrips->selectedItems()[0];
                break;
        }
        advanceBookingId = selectedItem->text(0).toLongLong();

        adv->updateInProgress = true;
        adv->initQuotationDialogue(advanceBookingId);
        adv->exec();
        if (adv->result() == QDialog::Accepted)
        {
            deleteAllAdvanceBookingFromTree();
            fillAdvanceBookingTree();
        }
    } else if (ui->tabWidgetAdvanceBooking->currentIndex() == ACCOUNTS_TAB) {
        NewQuotationDialogue *quot = new NewQuotationDialogue;
        qint64 bookingId;

        selectedItem = ui->treeWidgetAccounts->selectedItems()[0];
        bookingId = selectedItem->text(0).toLongLong();

        quot->updateInProgress = true;
        quot->initQuotationDialogue(bookingId);
        quot->exec();
        if (quot->result() == QDialog::Accepted)
        {
            deleteAllBookingFromTree();
            fillAccountsTree();
        }
    }
}

void MainWindow::on_actionDelete_triggered()
{
    QTreeWidgetItem *selectedItem;

    if (ui->tabWidgetTopLevel->currentIndex() == ADVANCE_BOOKING_TAB) {
        qint64 advanceBookingId;

        switch(ui->tabWidgetAdvanceBooking->currentIndex()) {
            case UPCOMING_TRIPS:
                selectedItem = ui->treeWidgetUpcomingTrips->selectedItems()[0];
                break;

            case ONGOING_TRIPS:
                selectedItem = ui->treeWidgetOngoingTrips->selectedItems()[0];
                break;

            case PAST_TRIPS:
                selectedItem = ui->treeWidgetPastTrips->selectedItems()[0];
                break;
        }

        advanceBookingId = selectedItem->text(0).toLongLong();
        DbManager::deleteAdvanceEntry(advanceBookingId);
        deleteAllAdvanceBookingFromTree();
        fillAdvanceBookingTree();
    } else if (ui->tabWidgetTopLevel->currentIndex() == ACCOUNTS_TAB) {
        qint64 bookingId;

        selectedItem = ui->treeWidgetAccounts->selectedItems()[0];
        bookingId = selectedItem->text(0).toLongLong();
        DbManager::deleteBookingEntry(bookingId);
        DbManager::deleteTripEntry(bookingId);
        DbManager::deleteExpenseEntry(bookingId);
        deleteAllBookingFromTree();
        fillAccountsTree();
    }
}

void MainWindow::deleteAllBookingFromTree()
{
    while (auto item = ui->treeWidgetAccounts->takeTopLevelItem(0))
        delete item;
}

void MainWindow::deleteAllAdvanceBookingFromTree()
{
    while (auto itemUpcoming = ui->treeWidgetUpcomingTrips->takeTopLevelItem(0))
        delete itemUpcoming;
    while (auto itemOngoing = ui->treeWidgetOngoingTrips->takeTopLevelItem(0))
        delete itemOngoing;
    while (auto itemPast = ui->treeWidgetPastTrips->takeTopLevelItem(0))
        delete itemPast;
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
