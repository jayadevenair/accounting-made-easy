#ifndef NEWQUOTATIONDIALOGUE_H
#define NEWQUOTATIONDIALOGUE_H

#include <QDialog>

namespace Ui {
class NewQuotationDialogue;
}

class NewQuotationDialogue : public QDialog
{
    Q_OBJECT

public:
    explicit NewQuotationDialogue(QWidget *parent = 0);
    ~NewQuotationDialogue();

private:
    Ui::NewQuotationDialogue *ui;
};

#endif // NEWQUOTATIONDIALOGUE_H
