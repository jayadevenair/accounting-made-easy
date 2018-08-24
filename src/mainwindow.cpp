#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newquotationdialogue.h"
#include <QString>
#include <QDebug>
#include <QDialog>

static const QString dbPath = "/home/jayadev/mydata.db";

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

    quot->exec();
    if (quot->result() == QDialog::Accepted)
    {
        quot->fillNewBookingCache(newBookingCache);
        addNewBookingToTree(newBookingCache);
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

void MainWindow::addNewBookingToTree(QHash <QString, QString> &newBookingCache)
{
    QTreeWidgetItem *newBookingNode = new QTreeWidgetItem;
    newBookingNode->setText(0, newBookingCache["bookingid"]);
    newBookingNode->setText(1, newBookingCache["bookingdate"]);
    newBookingNode->setText(2, newBookingCache["bookingtime"]);
    newBookingNode->setText(3, newBookingCache["customername"]);
    newBookingNode->setText(4, newBookingCache["destinations"]);
    newBookingNode->setText(5, newBookingCache["profit"]);

    ui->treeWidgetAllBooking->insertTopLevelItem(0, newBookingNode);
}

void MainWindow::on_action_Open_triggered()
{
    QTreeWidgetItem *selectedItem;
    QHash <QString, QString> newBookingCache;
    NewQuotationDialogue *quot = new NewQuotationDialogue;
    qint64 bookingId;

    selectedItem = ui->treeWidgetAllBooking->selectedItems()[0];
    bookingId = selectedItem->text(0).toLongLong();

    quot->initQuotationDialogue(bookingId);
    quot->exec();
    if (quot->result() == QDialog::Accepted)
    {
        quot->fillNewBookingCache(newBookingCache);
        updateBookingToTree(selectedItem, newBookingCache);
    }

}

void MainWindow::updateBookingToTree(QTreeWidgetItem *selectedItem, QHash <QString, QString> &newBookingCache)
{
    selectedItem->setText(0, newBookingCache["bookingid"]);
    selectedItem->setText(1, newBookingCache["bookingdate"]);
    selectedItem->setText(2, newBookingCache["bookingtime"]);
    selectedItem->setText(3, newBookingCache["customername"]);
    selectedItem->setText(4, newBookingCache["destinations"]);
    selectedItem->setText(5, newBookingCache["profit"]);
}
