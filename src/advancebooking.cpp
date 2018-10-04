#include "advancebooking.h"
#include "ui_advancebooking.h"
#include "dbmanager.h"
#include <QDebug>

AdvanceBooking::AdvanceBooking(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdvanceBooking)
{
    ui->setupUi(this);
    setupUiHuman();
}

AdvanceBooking::~AdvanceBooking()
{
    delete ui;
}

qint64 AdvanceBooking::getNextAdvanceBookingId(void)
{
    return DbManager::getMaxAdvanceBookingID() + 1;
}

void AdvanceBooking::extractFieldsFromDialogueBox(void)
{
    qint64 advanceBookingId;
    qint64 mobileNumber;

    mobileNumber = ui->lineEditMobileNo->text().toLong();
    if (updateInProgress)
    {
        advanceBookingId = advance.advanceBookingId;
    }
    else
    {
        advanceBookingId = getNextAdvanceBookingId();
    }

    /* Extract User Information */
    user.mobileNumber = mobileNumber;

    QLineEdit *firstName = ui->lineEditFirstName;
    user.firstName = firstName->text();

    QLineEdit *lastName = ui->lineEditLastName;
    user.lastName = lastName->text();

    QLineEdit *addressLine1 = ui->lineEditAddressLine1;
    user.addressLine1 = addressLine1->text();

    QLineEdit *addressLine2 = ui->lineEditAddressLine2;
    user.addressLine2 = addressLine2->text();

    QLineEdit *city = ui->lineEditCity;
    user.city = city->text();

    QLineEdit *district = ui->lineEditDistrict;
    user.district = district->text();

    QLineEdit *state = ui->lineEditState;
    user.state = state->text();

    QLineEdit *pinCode = ui->lineEditPinCode;
    user.pinCode = pinCode->text().toInt();

    /* Extract advance data */
    advance.advanceBookingId = advanceBookingId;
    advance.mobileNumber = mobileNumber;

    QLineEdit *adminName = ui->lineEditAdminName;
    advance.adminName = adminName->text();

    if (!updateInProgress)
    {
        QDateTime currentdateTime = QDateTime::currentDateTime();
        advance.advanceBookingDate = currentdateTime.date().toString(Qt::ISODate);
        advance.advanceBookingTime = currentdateTime.time().toString();
    }

    QLineEdit *advanceAmount = ui->lineEditAdvanceAmount;
    advance.advance = advanceAmount->text().toLongLong();

    QLineEdit *perHeadAmount = ui->lineEditPerHeadAmount;
    advance.perHeadAmount = perHeadAmount->text().toLongLong();

    QSpinBox *numPassengers = ui->spinBoxNoPassengers;
    advance.numPassengers = numPassengers->value();

    QLineEdit *totalAmount = ui->lineEditTotalAmount;
    advance.totalAmount = totalAmount->text().toLongLong();

    QLineEdit *destinations = ui->lineEditDestinations;
    advance.destination = destinations->text();

    QDateTimeEdit *departureDateTime = ui->dateTimeEditDeparture;
    advance.departureDate = departureDateTime->date().toString(Qt::ISODate);
    advance.departureTime = departureDateTime->time().toString();

    QDateTimeEdit *arrivalDateTime = ui->dateTimeEditArrival;
    advance.arrivalDate = arrivalDateTime->date().toString(Qt::ISODate);
    advance.arrivalTime = arrivalDateTime->time().toString();

    QLineEdit *vehicle = ui->lineEditVehicle;
    advance.vehicle = vehicle->text();
}

void AdvanceBooking::on_buttonBox_accepted()
{
    extractFieldsFromDialogueBox();
    DbManager::addAdvanceEntry(this->advance);
    DbManager::addUserEntry(this->user);
}

void AdvanceBooking::on_buttonBox_rejected()
{
    qDebug() << "Pressed advance dialogue cancel button";
}

void AdvanceBooking::setupUiHuman(void)
{
    QLineEdit *advanceAmount = ui->lineEditAdvanceAmount;
    advanceAmount->setValidator(new QIntValidator(this));

    QLineEdit *perHeadAmount = ui->lineEditPerHeadAmount;
    perHeadAmount->setValidator(new QIntValidator(this));

    QDateTimeEdit *departureDateTime = ui->dateTimeEditDeparture;
    departureDateTime->setDateTime(QDateTime::currentDateTime());

    QDateTimeEdit *arrivalDateTime = ui->dateTimeEditArrival;
    arrivalDateTime->setDateTime(QDateTime::currentDateTime());
}

void AdvanceBooking::fillNewAdvanceBookingCache(QHash <QString, QString> &newBookingCache) {
    newBookingCache["bookingid"] = QString::number(advance.advanceBookingId);
    newBookingCache["bookingdatetime"]= advance.advanceBookingDate + " " + advance.advanceBookingTime;
    newBookingCache["customername"] = user.firstName + " " + user.lastName;
    newBookingCache["mobilenumber"] = QString::number(user.mobileNumber);
    newBookingCache["destinations"]= advance.destination;
    newBookingCache["departuredatetime"]= advance.departureDate + " " + advance.departureTime;
    newBookingCache["arrivaldatetime"]= advance.arrivalDate + " " + advance.arrivalTime;
    newBookingCache["advance"]= QString::number(advance.advance);
    newBookingCache["numpassengers"]= QString::number(advance.numPassengers);
    newBookingCache["perheadamount"]= QString::number(advance.perHeadAmount);
    newBookingCache["totalamount"]= QString::number(advance.totalAmount);
    newBookingCache["mobilenumber"]= QString::number(advance.mobileNumber);
}

void AdvanceBooking::initQuotationDialogue(qint64 advanceBookingId)
{
    qint64 mobileNo;

    DbManager::getAdvanceEntry(advance, advanceBookingId);
    mobileNo = advance.mobileNumber;
    DbManager::getUserEntry(user, mobileNo);

    /* user details */
    ui->lineEditFirstName->setText(user.firstName);
    ui->lineEditLastName->setText(user.lastName);
    ui->lineEditAddressLine1->setText(user.addressLine1);
    ui->lineEditAddressLine2->setText(user.addressLine2);
    ui->lineEditCity->setText(user.city);
    ui->lineEditDistrict->setText(user.district);
    ui->lineEditState->setText(user.state);
    ui->lineEditPinCode->setText(QString::number(user.pinCode));
    ui->lineEditMobileNo->setText(QString::number(user.mobileNumber));

    /* advance details */
    ui->lineEditDestinations->setText(advance.destination);
    ui->dateTimeEditDeparture->setDate(QDate::fromString(advance.departureDate, Qt::ISODate));
    ui->dateTimeEditDeparture->setTime(QTime::fromString(advance.departureTime));
    ui->dateTimeEditArrival->setDate(QDate::fromString(advance.arrivalDate, Qt::ISODate));
    ui->dateTimeEditArrival->setTime(QTime::fromString(advance.arrivalTime));
    ui->lineEditVehicle->setText(advance.vehicle);
    ui->spinBoxNoPassengers->setValue(advance.numPassengers);
    ui->lineEditPerHeadAmount->setText(QString::number(advance.perHeadAmount));
    ui->lineEditTotalAmount->setText(QString::number(advance.totalAmount));
    ui->lineEditAdvanceAmount->setText(QString::number(advance.advance));
    ui->lineEditAdminName->setText(advance.adminName);
}

void AdvanceBooking::on_lineEditPerHeadAmount_textChanged(const QString &arg1)
{
    qint16 numPassengers;

    numPassengers = ui->spinBoxNoPassengers->value();
    calculateTotalAmount(numPassengers, arg1.toInt());
}

void AdvanceBooking::calculateTotalAmount(qint16 numPassengers, qint32 perHeadAmount) {
    qint64 totalAmount;

    totalAmount = numPassengers * perHeadAmount;
    ui->lineEditTotalAmount->setText(QString::number(totalAmount));
}


void AdvanceBooking::on_spinBoxNoPassengers_valueChanged(int arg1)
{
    qint32 perHeadAmount;

    perHeadAmount = ui->lineEditPerHeadAmount->text().toInt();
    calculateTotalAmount(arg1, perHeadAmount);
}
