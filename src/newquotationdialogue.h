#ifndef NEWQUOTATIONDIALOGUE_H
#define NEWQUOTATIONDIALOGUE_H

#include <QDialog>
#include "dbmanager.h"
#include "mainwindow.h"

namespace Ui {
class NewQuotationDialogue;
}

class NewQuotationDialogue : public QDialog
{
    Q_OBJECT

public:
    explicit NewQuotationDialogue(QWidget *parent = 0);
    ~NewQuotationDialogue();
    void fillNewBookingCache(QHash <QString, QString> &newBookingCache);
    void initQuotationDialogue(qint64 bookingId);
    bool updateInProgress;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_lineEditFood_textChanged(const QString &arg1);

    void on_lineEditAccomodation_textChanged(const QString &arg1);

    void on_lineEditTransport_textChanged(const QString &arg1);

    void on_lineEditGuideCharges_textChanged(const QString &arg1);

    void on_lineEditOthers_textChanged(const QString &arg1);

    void on_lineEditPerHeadAmount_textChanged(const QString &arg1);

    void on_lineEditTotalExpenses_textChanged(const QString &arg1);

    void on_spinBoxNoPassengers_valueChanged(int arg1);

private:
    Ui::NewQuotationDialogue *ui;
    void setupUiHuman(void);
    void extractFieldsFromDialogueBox(void);
    qint64 getNextBookingId(void);
    void calculateProfit(void);
    void calculateTotalExpense(void);
    DbUser user;
    DbExpense expense;
    DbBooking booking;
    DbTrip trip;
};

#endif // NEWQUOTATIONDIALOGUE_H
