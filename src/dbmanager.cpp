#include "dbmanager.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

DbManager::DbManager(const QString& path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database fail";
    } else
    {
        qDebug() << "Database: connection ok";
    }
    DbManager::createTables();
}

DbManager::~DbManager()
{
    if (m_db.isOpen())
        m_db.close();
}

void DbManager::createUserTable(void)
{
    QSqlQuery qry;

    qry.prepare("CREATE TABLE IF NOT EXISTS user"
                "(mobileno INTEGER UNIQUE PRIMARY KEY, "
                "firstname VARCHAR(30), "
                "lastname VARCHAR(30), "
                "addressline1 VARCHAR(30), "
                "addressline2 VARCHAR(30), "
                "city VARCHAR(30), "
                " district VARCHAR(30), "
                "state VARCHAR(30), "
                "pincode INTIGER)");
    if(!qry.exec())
    {
        qDebug() << qry.lastError();
    }
    else
    {
        qDebug() << "user Table created!";
    }
}

void DbManager::createBookingTable(void)
{
    QSqlQuery qry;

    qry.prepare("CREATE TABLE IF NOT EXISTS booking"
                "(bookingid INTEGER UNIQUE PRIMARY KEY, "
                "mobilenumber INTIGER, "
                "admin VARCHAR(30), "
                "date VARCHAR(30), "
                "time VARCHAR(30))");
    if(!qry.exec())
    {
        qDebug() << qry.lastError();
    }
    else
    {
        qDebug() << "booking Table created!";
    }
}

void DbManager::createTripTable(void)
{
    QSqlQuery qry;

    qry.prepare("CREATE TABLE IF NOT EXISTS trip"
                "(bookingid INTEGER UNIQUE PRIMARY KEY, "
                "destination VARCHAR(30), "
                "departuredate VARCHAR(30), "
                "departuretime VARCHAR(30), "
                "arrivaldate VARCHAR(30), "
                "arrivaltime VARCHAR(30), "
                "numpassengers INITIGER, "
                "vehicle VARCHAR(30))");
    if(!qry.exec())
    {
        qDebug() << qry.lastError();
    }
    else
    {
        qDebug() << "trip Table created!";
    }
}

void DbManager::createExpenseTable(void)
{
    QSqlQuery qry;

    qry.prepare("CREATE TABLE IF NOT EXISTS expense"
                "(bookingid INTEGER UNIQUE PRIMARY KEY, "
                "food INTIGER, "
                "accomodation INTIGER, "
                "transport INTIGER, "
                "others INTIGER, "
                "totalexpense INTIGER, "
                "totalreturn INTIGER, "
                "profit INTIGER)");
    if(!qry.exec())
    {
        qDebug() << qry.lastError();
    }
    else
    {
        qDebug() << "expense Table created!";
    }
}

void DbManager::createTables(void)
{
    createUserTable();
    createBookingTable();
    createTripTable();
    createExpenseTable();
}

void DbManager::_addExpense(const DbExpense& expense)
{
    QSqlQuery qry;

    qry.prepare("INSERT INTO expense (bookingid, food, accomodation, transport, others, "
                "totalexpense, totalreturn, profit) VALUES (:bookingid, :food, "
                ":accomodation, :transport, :others, :totalexpense, :totalreturn, :profit)");
    qry.bindValue(":bookingid", expense.bookingId);
    qry.bindValue(":food", expense.food);
    qry.bindValue(":accomodation", expense.accomodation);
    qry.bindValue(":transport", expense.transport);
    qry.bindValue(":others", expense.others);
    qry.bindValue(":totalexpense", expense.totalExpense);
    qry.bindValue(":totalreturn", expense.totalReturn);
    qry.bindValue(":profit", expense.profit);

     if( !qry.exec() )
       qDebug() << qry.lastError();
     else
       qDebug( "Inserted expense entry!" );
}

void DbManager::_addUser(const DbUser& user)
{
    QSqlQuery qry;

    qry.prepare("INSERT INTO user (mobileno, firstname, lastname, addressline1, addressline2, "
                "city, district, state, pincode) VALUES (:mobileno, :firstname, "
                ":lastname, :addressline1, :addressline2, :city, :district, :profit, :pincode)");
    qry.bindValue(":mobileno", user.mobileNumber);
    qry.bindValue(":firstname", user.firstName);
    qry.bindValue(":lastname", user.lastName);
    qry.bindValue(":addressline1", user.addressLine1);
    qry.bindValue(":addressline2", user.addressLine2);
    qry.bindValue(":city", user.city);
    qry.bindValue(":district", user.district);
    qry.bindValue(":state", user.state);
    qry.bindValue(":pincode", user.pinCode);

     if( !qry.exec() )
       qDebug() << qry.lastError();
     else
       qDebug( "Inserted user entry!" );
}

void DbManager::_addBooking(const DbBooking& booking)
{
    QSqlQuery qry;

    qry.prepare("INSERT INTO booking (bookingid, mobilenumber, admin, date, time)"
                "VALUES (:bookingid, :mobilenumber, :admin, :date, :time)");
    qry.bindValue(":bookingid", booking.bookingId);
    qry.bindValue(":mobilenumber", booking.mobileNumber);
    qry.bindValue(":admin", booking.adminName);
    qry.bindValue(":date", booking.currentDate);
    qry.bindValue(":time", booking.currentTime);

     if( !qry.exec() )
       qDebug() << qry.lastError();
     else
       qDebug( "Inserted booking entry!" );
}

void DbManager::_addTrip(const DbTrip& trip)
{
    QSqlQuery qry;

    qry.prepare("INSERT INTO trip (bookingid, destination, departuredate, departuretime, "
                "arrivaldate, arrivaltime, numpassengers, vehicle) VALUES (:bookingid, "
                ":destination, :departuredate, :departuretime, :arrivaldate, :arrivaltime, "
                ":numpassengers, :vehicle)");
    qry.bindValue(":bookingid", trip.bookingId);
    qry.bindValue(":destination", trip.destination);
    qry.bindValue(":departuredate", trip.departureDate);
    qry.bindValue(":departuretime", trip.departureTime);
    qry.bindValue(":arrivaldate", trip.arrivalDate);
    qry.bindValue(":arrivaltime", trip.arrivalTime);
    qry.bindValue(":numpassengers", trip.numPassengers);
    qry.bindValue(":vehicle", trip.vehicle);

     if( !qry.exec() )
       qDebug() << qry.lastError();
     else
       qDebug( "Inserted trip entry!" );
}

void DbManager::addExpenseEntry(const DbExpense& expense)
{
    _addExpense(expense);
}

void DbManager::addUserEntry(const DbUser& user)
{
    _addUser(user);
}

void DbManager::addBookingEntry(const DbBooking& booking)
{
    _addBooking(booking);
}

void DbManager::addTripEntry(const DbTrip& trip)
{
    _addTrip(trip);
}
