#include "reportdialoguebox.h"
#include "ui_reportdialoguebox.h"
#include "dbmanager.h"
#include <QDebug>

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

void ReportDialogueBox::on_buttonBox_accepted()
{
    qint32 totalExpense;
    qint32 totalReturn;

    if (ui->radioButtonYearly->isChecked())
    {
        QString year;

        year = QString::number(ui->dateEditYearly->date().year());
        totalExpense = DbManager::getTotalExpenseYearly(year);
        totalReturn = DbManager::getTotalReturnYearly(year);
    }
    else if (ui->radioButtonMonthly->isChecked())
    {
        QString month;

        month = QString::number(ui->dateEditMonthly->date().month());
        totalExpense = DbManager::getTotalExpenseMonthly(month);
        totalReturn = DbManager::getTotalReturnMonthly(month);
    }
    else if (ui->radioButtonDaily->isChecked())
    {
        QString day;

        day = ui->dateEditDaily->date().toString(Qt::ISODate);
        qDebug() << "JAYADEV " << day;
        totalExpense = DbManager::getTotalExpenseDaily(day);
        totalReturn = DbManager::getTotalReturnDaily(day);
    }
    else if (ui->radioButtonCustom->isChecked())
    {
        QString startDate;
        QString startTime;
        QString endDate;
        QString endTime;

        startDate = ui->dateTimeEditStart->date().toString(Qt::ISODate);
        endDate = ui->dateTimeEditEnd->date().toString(Qt::ISODate);
        startTime = ui->dateTimeEditStart->time().toString();
        endTime = ui->dateTimeEditEnd->time().toString();
        totalExpense = DbManager::getTotalExpenseCustom(startDate, startTime, endDate, endTime);
        totalReturn = DbManager::getTotalReturnCustom(startDate, startTime, endDate, endTime);
    }

    qDebug() << "JAYADEV retrun " << totalReturn << "expense " << totalExpense << "Profit " <<
                (totalReturn-totalExpense);
}

void ReportDialogueBox::on_buttonBox_rejected()
{

}
