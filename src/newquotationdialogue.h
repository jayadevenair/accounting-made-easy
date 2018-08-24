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

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::NewQuotationDialogue *ui;
    void setupUiHuman(void);
    void extractFieldsFromDialogueBox(void);
    qint64 getNextBookingId(void);
    DbUser user;
    DbExpense expense;
    DbBooking booking;
    DbTrip trip;
};

#endif // NEWQUOTATIONDIALOGUE_H
