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

private:
    Ui::AdvanceBooking *ui;
    void setupUiHuman(void);
    void extractFieldsFromDialogueBox(void);
    qint64 getNextAdvanceBookingId(void);
    DbUser user;
    DbExpense expense;
    DbBooking booking;
    DbTrip trip;
    DbAdvance advance;
};
#endif // ADVANCEBOOKING_H
