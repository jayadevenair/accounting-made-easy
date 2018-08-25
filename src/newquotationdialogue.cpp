#include "newquotationdialogue.h"
#include "ui_newquotationdialogue.h"
#include "dbmanager.h"
#include <QDebug>

NewQuotationDialogue::NewQuotationDialogue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewQuotationDialogue)
{
    ui->setupUi(this);
    setupUiHuman();
}

NewQuotationDialogue::~NewQuotationDialogue()
{
    delete ui;
}

qint64 NewQuotationDialogue::getNextBookingId(void)
{
    return DbManager::getMaxBookingID() + 1;
}

void NewQuotationDialogue::extractFieldsFromDialogueBox(void)
{
    qint64 bookingId;
    qint64 mobileNumber;

    /* Extract Info common for all the tables*/
    mobileNumber = ui->lineEditMobileNo->text().toLong();
    if (updateInProgress)
    {
        bookingId = booking.bookingId;
    }
    else
    {
        bookingId = getNextBookingId();
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


    /* Extract Trip data */
    trip.bookingId = bookingId;

    QLineEdit *destinations = ui->lineEditDestinations;
    trip.destination = destinations->text();

    QDateTimeEdit *departureDateTime = ui->dateTimeEditDeparture;
    trip.departureDate = departureDateTime->date().toString();
    trip.departureTime = departureDateTime->time().toString();

    QDateTimeEdit *arrivalDateTime = ui->dateTimeEditArrival;
    trip.arrivalDate = arrivalDateTime->date().toString();
    trip.arrivalTime = arrivalDateTime->time().toString();

    QLineEdit *vehicle = ui->lineEditVehicle;
    trip.vehicle = vehicle->text();

    QLineEdit *guideName = ui->lineEditGuideName;
    trip.guideName = guideName->text();

    QSpinBox *numPassengers = ui->spinBoxNoPassengers;
    trip.numPassengers = numPassengers->value();

    QSpinBox *numStaffs = ui->spinBoxNoStaffs;
    trip.numStaffs = numStaffs->value();


    /* Extract expense data */
    expense.bookingId = bookingId;

    QLineEdit *food = ui->lineEditFood;
    expense.food = food->text().toInt();

    QLineEdit *accomodation = ui->lineEditAccomodation;
    expense.accomodation = accomodation->text().toInt();

    QLineEdit *transport = ui->lineEditTransport;
    expense.transport = transport->text().toInt();

    QLineEdit *guideCharges = ui->lineEditGuideCharges;
    expense.guideCharges = guideCharges->text().toInt();

    QLineEdit *others = ui->lineEditOthers;
    expense.others = others->text().toInt();

    QLineEdit *totalExpenses = ui->lineEditTotalExpenses;
    expense.totalExpense = totalExpenses->text().toInt();

    QLineEdit *perHeadAmount = ui->lineEditPerHeadAmount;
    expense.perHeadAmount = perHeadAmount->text().toInt();

    expense.profit = (expense.perHeadAmount * trip.numPassengers) - (expense.totalExpense);


    /* Extract booking data */
    booking.bookingId = bookingId;
    booking.mobileNumber = mobileNumber;

    QLineEdit *adminName = ui->lineEditAdminName;
    booking.adminName = adminName->text();

    if (!updateInProgress)
    {
        QDateTime currentdateTime = QDateTime::currentDateTime();
        booking.bookingDate = currentdateTime.date().toString();
        booking.bookingTime = currentdateTime.time().toString();
    }
}

void NewQuotationDialogue::on_buttonBox_accepted()
{
    extractFieldsFromDialogueBox();
    DbManager::addBookingEntry(this->booking);
    DbManager::addUserEntry(this->user);
    DbManager::addTripEntry(this->trip);
    DbManager::addExpenseEntry(this->expense);
}

void NewQuotationDialogue::on_buttonBox_rejected()
{
    qDebug() << "Pressed cancel button";
}

void NewQuotationDialogue::setupUiHuman(void)
{
    QLineEdit *foodExpense = ui->lineEditFood;
    foodExpense->setValidator(new QIntValidator(this));

    QLineEdit *accomodationExpense = ui->lineEditAccomodation;
    accomodationExpense->setValidator(new QIntValidator(this));

    QLineEdit *transportExpense = ui->lineEditTransport;
    transportExpense->setValidator(new QIntValidator(this));

    QLineEdit *otherExpense = ui->lineEditOthers;
    otherExpense->setValidator(new QIntValidator(this));

    QLineEdit *guideChargesExpense = ui->lineEditGuideCharges;
    guideChargesExpense->setValidator(new QIntValidator(this));

    QLineEdit *totalExpense = ui->lineEditTotalExpenses;
    totalExpense->setValidator(new QIntValidator(this));

    QLineEdit *perHeadAmount = ui->lineEditPerHeadAmount;
    perHeadAmount->setValidator(new QIntValidator(this));
}

void NewQuotationDialogue::fillNewBookingCache(QHash <QString, QString> &newBookingCache) {
    newBookingCache["bookingid"] = QString::number(booking.bookingId);
    newBookingCache["bookingdate"]= booking.bookingDate;
    newBookingCache["bookingtime"]= booking.bookingTime;
    newBookingCache["customername"] = user.firstName + " " + user.lastName;
    newBookingCache["destinations"]= trip.destination;
    newBookingCache["profit"]= QString::number(expense.profit);
}

void NewQuotationDialogue::initQuotationDialogue(qint64 bookingId)
{
    qint64 mobileNo;

    DbManager::getBookingEntry(booking, bookingId);
    DbManager::getExpenseEntry(expense, bookingId);
    mobileNo = booking.mobileNumber;
    DbManager::getUserEntry(user, mobileNo);
    DbManager::getTripEntry(trip, bookingId);

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

    /* trip details */
    ui->lineEditDestinations->setText(trip.destination);
    ui->dateTimeEditDeparture->setDate(QDate::fromString(trip.departureDate));
    ui->dateTimeEditDeparture->setTime(QTime::fromString(trip.departureTime));
    ui->dateTimeEditArrival->setDate(QDate::fromString(trip.arrivalDate));
    ui->dateTimeEditArrival->setTime(QTime::fromString(trip.arrivalTime));
    ui->lineEditVehicle->setText(trip.vehicle);
    ui->spinBoxNoPassengers->setValue(trip.numPassengers);
    ui->spinBoxNoStaffs->setValue(trip.numStaffs);
    ui->lineEditGuideName->setText(trip.guideName);

    /* expense details */
    ui->lineEditFood->setText(QString::number(expense.food));
    ui->lineEditAccomodation->setText(QString::number(expense.accomodation));
    ui->lineEditTransport->setText(QString::number(expense.transport));
    ui->lineEditGuideCharges->setText(QString::number(expense.guideCharges));
    ui->lineEditOthers->setText(QString::number(expense.others));
    ui->lineEditTotalExpenses->setText(QString::number(expense.totalExpense));
    ui->lineEditPerHeadAmount->setText(QString::number(expense.perHeadAmount));
    ui->lineEditBalance->setText(QString::number(expense.profit));
    ui->lineEditAdminName->setText(booking.adminName);
}
