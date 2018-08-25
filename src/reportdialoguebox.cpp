#include "reportdialoguebox.h"
#include "ui_reportdialoguebox.h"

ReportDialogueBox::ReportDialogueBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReportDialogueBox)
{
    ui->setupUi(this);
}

ReportDialogueBox::~ReportDialogueBox()
{
    delete ui;
}
