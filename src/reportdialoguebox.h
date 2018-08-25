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

private:
    Ui::ReportDialogueBox *ui;
};

#endif // REPORTDIALOGUEBOX_H
