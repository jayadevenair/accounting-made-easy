#ifndef REPORTDIALOGUEBOX_H
#define REPORTDIALOGUEBOX_H

#include <QDialog>

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

private:
    Ui::ReportDialogueBox *ui;
    void setupUiHuman(void);
};

#endif // REPORTDIALOGUEBOX_H
