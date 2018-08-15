#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newquotationdialogue.h"
#include <QString>

static const QString dbPath = "/home/jayadev/mydata.db";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = new DbManager(dbPath);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete db;
}

void MainWindow::on_action_New_triggered()
{
    NewQuotationDialogue *quot = new NewQuotationDialogue;
    quot->exec();
}
