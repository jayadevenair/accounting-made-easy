#ifndef REPORTDIALOGUEBOX_H
#define REPORTDIALOGUEBOX_H

#include <QDialog>
#include <QWebEnginePage>

namespace Ui {
class ReportDialogueBox;
}

class ReportDialogueBox : public QDialog
{
    Q_OBJECT

public:
    explicit ReportDialogueBox(QWidget *parent = 0);
    ~ReportDialogueBox();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void pdfPrintingFinishedReport(const QString &filePath, bool success);

    void loadFinishedReport(bool ok);

private:
    Ui::ReportDialogueBox *ui;
    void setupUiHuman(void);
    void createReportPdf(void);
    QWebEnginePage *mreportPage;
};

#endif // REPORTDIALOGUEBOX_H
