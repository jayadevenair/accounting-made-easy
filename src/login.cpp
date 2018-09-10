#include "login.h"
#include "ui_login.h"
#include <QMessageBox>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_buttonBox_accepted()
{

    if((ui->lineEditUserName->text()=="admin") && (ui->lineEditPassword->text()=="12345"))
    {
        QMessageBox::about(this, tr("Login success"), tr("<p>Welcome...</p>"));
        this->setResult(QDialog::Accepted);
    } else
    {
        QMessageBox::about(this, tr("Login unsuccess"), tr("<p>Wrong password</p>"));
        this->setResult(QDialog::Rejected);
    }
}

void Login::on_buttonBox_rejected()
{

}
