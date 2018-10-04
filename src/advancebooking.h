#ifndef ADVANCEBOOKING_H
#define ADVANCEBOOKING_H

#include <QDialog>
#include "dbmanager.h"

namespace Ui {
class AdvanceBooking;
};

class AdvanceBooking : public QDialog
{
    Q_OBJECT

public:
    explicit AdvanceBooking(QWidget *parent = nullptr);
    ~AdvanceBooking();
    void fillNewAdvanceBookingCache(QHash <QString, QString> &newAdvanceBookingCache);
    void initQuotationDialogue(qint64 bookingId);
    bool updateInProgress;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_lineEditPerHeadAmount_textChanged(const QString &arg1);

    void on_spinBoxNoPassengers_valueChanged(int arg1);

private:
    Ui::AdvanceBooking *ui;
    void setupUiHuman(void);
    void extractFieldsFromDialogueBox(void);
    qint64 getNextAdvanceBookingId(void);
    void calculateTotalAmount(qint16 numPassengers, qint32 perHeadAmount);
    DbUser user;
    DbExpense expense;
    DbBooking booking;
    DbTrip trip;
    DbAdvance advance;
};
#endif // ADVANCEBOOKING_H
