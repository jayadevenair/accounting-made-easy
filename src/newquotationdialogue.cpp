#include "newquotationdialogue.h"
#include "ui_newquotationdialogue.h"

NewQuotationDialogue::NewQuotationDialogue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewQuotationDialogue)
{
    ui->setupUi(this);
}

NewQuotationDialogue::~NewQuotationDialogue()
{
    delete ui;
}
