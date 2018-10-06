#include "reportdialoguebox.h"
#include "ui_reportdialoguebox.h"
#include "dbmanager.h"
#include <QDebug>
#include <QPrinter>
#include <QFile>
#include <QWebEnginePage>
#include <QMessageBox>

ReportDialogueBox::ReportDialogueBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReportDialogueBox)
{
    ui->setupUi(this);
    setupUiHuman();
    mreportPage = new QWebEnginePage;
    connect(mreportPage, &QWebEnginePage::loadFinished,
            this, &ReportDialogueBox::loadFinishedReport);
    connect(mreportPage, &QWebEnginePage::pdfPrintingFinished,
            this, &ReportDialogueBox::pdfPrintingFinishedReport);
}

ReportDialogueBox::~ReportDialogueBox()
{
    delete ui;
    delete mreportPage;
}

void ReportDialogueBox::setupUiHuman(void)
{
    QDateEdit *startDate = ui->dateEditStart;
    startDate->setDate(QDate::currentDate());

    QDateEdit *endDate = ui->dateEditEnd;
    endDate->setDate(QDate::currentDate());

    QDateEdit *daily = ui->dateEditDaily;
    daily->setDate(QDate::currentDate());

    QDateEdit *monthly = ui->dateEditMonthly;
    monthly->setDate(QDate::currentDate());

    QDateEdit *yearly = ui->dateEditYearly;
    yearly->setDate(QDate::currentDate());

    QRadioButton *monthlyRadio = ui->radioButtonMonthly;
    monthlyRadio->setChecked(true);
}

void ReportDialogueBox::on_buttonBox_accepted()
{
    qint32 totalExpense;
    qint32 totalReturn;
    qint32 totalProfit;
    QMessageBox msgBox;

    if (ui->radioButtonYearly->isChecked())
    {
        QString year;

        year = QString::number(ui->dateEditYearly->date().year());
        msgBox.setText(QString("<b>Expense Report for %1<\b>").arg(year));
        totalExpense = DbManager::getTotalExpenseYearly(year);
        totalReturn = DbManager::getTotalReturnYearly(year);
        totalProfit = DbManager::getTotalProfitYearly(year);
    }
    else if (ui->radioButtonMonthly->isChecked())
    {
        QString month;
        QString monthString;

        month = QString::number(ui->dateEditMonthly->date().month());
        monthString = ui->dateEditMonthly->date().toString("MMMM yyyy");
        msgBox.setText(QString("<b>Expense Report for %1<\b>").arg(monthString));
        totalExpense = DbManager::getTotalExpenseMonthly(month);
        totalReturn = DbManager::getTotalReturnMonthly(month);
        totalProfit = DbManager::getTotalProfitMonthly(month);
    }
    else if (ui->radioButtonDaily->isChecked())
    {
        QString day;
        QString dayString;


        day = ui->dateEditDaily->date().toString(Qt::ISODate);
        dayString = ui->dateEditDaily->date().toString("dd MMMM yyyy");
        msgBox.setText(QString("<b>Expense Report for %1<\b>").arg(dayString));
        totalExpense = DbManager::getTotalExpenseDaily(day);
        totalReturn = DbManager::getTotalReturnDaily(day);
        totalProfit = DbManager::getTotalProfitDaily(day);
    }
    else if (ui->radioButtonCustom->isChecked())
    {
        QString startDate;
        QString startTime;
        QString endDate;
        QString endTime;
        QString startString;
        QString endString;

        startString = ui->dateEditStart->date().toString("dd MMMM yyyy");
        endString = ui->dateEditEnd->date().toString("dd MMMM yyyy");
        msgBox.setText(QString("<b>Expense Report for \"%1\" to \"%2\"<\b>").arg(startString, endString));
        startDate = ui->dateEditStart->date().toString(Qt::ISODate);
        endDate = ui->dateEditEnd->date().toString(Qt::ISODate);
        totalExpense = DbManager::getTotalExpenseCustom(startDate, endDate);
        totalReturn = DbManager::getTotalReturnCustom(startDate, endDate);
        totalProfit = DbManager::getTotalProfitCustom(startDate, endDate);
    }

    QString info = QString("Total Income  : %1\nTotal Expense : %2\n"
                           "Total Profit  : %3\n").arg(QString::number(totalReturn),
                                                      QString::number(totalExpense),
                                                      QString::number(totalProfit));
    msgBox.setInformativeText(info);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();

    //createReportPdf();
}

void ReportDialogueBox::loadFinishedReport(bool ok)
{
    if (!ok) {
        QTextStream(stderr)
            << tr("failed to load reporthtml") << "\n";
        return;
    }
    mreportPage->printToPdf((QString)"/home/ejayadev/report.pdf");
}

void ReportDialogueBox::pdfPrintingFinishedReport(const QString &filePath, bool success)
{
    if (!success) {
        QTextStream(stderr)
            << tr("failed to generate report at '%1'").arg(filePath) << "\n";
    } else {
        QTextStream(stderr)
            << tr("successfully generated report at '%1'").arg(filePath) << "\n";
    }
}

void ReportDialogueBox::createReportPdf(void) {
    QFile file("/home/ejayadev/work/fir/html-invoice-template/index.html");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    QString text;
    text = in.readAll();
    file.close();

    mreportPage->setHtml(text);
}

void ReportDialogueBox::on_buttonBox_rejected()
{

}
