#include "reportdialoguebox.h"
#include "ui_reportdialoguebox.h"

ReportDialogueBox::ReportDialogueBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReportDialogueBox)
{
    ui->setupUi(this);
    setupUiHuman();
}

ReportDialogueBox::~ReportDialogueBox()
{
    delete ui;
}

void ReportDialogueBox::setupUiHuman(void)
{
    QDateTimeEdit *startDateTime = ui->dateTimeEditStart;
    startDateTime->setDateTime(QDateTime::currentDateTime());

    QDateTimeEdit *endDateTime = ui->dateTimeEditEnd;
    endDateTime->setDateTime(QDateTime::currentDateTime());

    QDateEdit *daily = ui->dateEditDaily;
    daily->setDate(QDate::currentDate());

    QDateEdit *monthly = ui->dateEditMonthly;
    monthly->setDate(QDate::currentDate());

    QDateEdit *yearly = ui->dateEditYearly;
    yearly->setDate(QDate::currentDate());
}
