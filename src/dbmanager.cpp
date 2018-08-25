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
                "district VARCHAR(30), "
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
                "bookingdate VARCHAR(30), "
                "bookingtime VARCHAR(30))");
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
                "numstaffs INTIGER, "
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
                "guidecharges INTIGER, "
                "others INTIGER, "
                "totalexpense INTIGER, "
                "perheadamount INIGER, "
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

    qry.prepare("REPLACE INTO expense (bookingid, food, accomodation, transport, guidecharges, "
                "others, totalexpense, perheadamount, totalreturn, profit) VALUES (:bookingid, "
                ":food, :accomodation, :transport, :guidecharges, :others, :totalexpense, "
                ":perheadamount, :totalreturn, :profit)");
    qry.bindValue(":bookingid", expense.bookingId);
    qry.bindValue(":food", expense.food);
    qry.bindValue(":accomodation", expense.accomodation);
    qry.bindValue(":transport", expense.transport);
    qry.bindValue(":guidecharges", expense.guideCharges);
    qry.bindValue(":others", expense.others);
    qry.bindValue(":totalexpense", expense.totalExpense);
    qry.bindValue(":perheadamount", expense.perHeadAmount);
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

    qry.prepare("REPLACE INTO user (mobileno, firstname, lastname, addressline1, addressline2, "
                "city, district, state, pincode) VALUES (:mobileno, :firstname, "
                ":lastname, :addressline1, :addressline2, :city, :district, :state, "
                ":pincode)");
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

    qry.prepare("REPLACE INTO booking (bookingid, mobilenumber, admin, bookingdate, "
                "bookingtime) VALUES (:bookingid, :mobilenumber, :admin, :bookingdate, "
                ":bookingtime)");
    qry.bindValue(":bookingid", booking.bookingId);
    qry.bindValue(":mobilenumber", booking.mobileNumber);
    qry.bindValue(":admin", booking.adminName);
    qry.bindValue(":bookingdate", booking.bookingDate);
    qry.bindValue(":bookingtime", booking.bookingTime);

     if( !qry.exec() )
       qDebug() << qry.lastError();
     else
       qDebug( "Inserted booking entry!" );
}

void DbManager::_addTrip(const DbTrip& trip)
{
    QSqlQuery qry;

    qry.prepare("REPLACE INTO trip (bookingid, destination, departuredate, departuretime, "
                "arrivaldate, arrivaltime, numpassengers, numstaffs, vehicle) "
                "VALUES (:bookingid, :destination, :departuredate, :departuretime, :arrivaldate, "
                ":arrivaltime, :numpassengers, :numstaffs, :vehicle)");
    qry.bindValue(":bookingid", trip.bookingId);
    qry.bindValue(":destination", trip.destination);
    qry.bindValue(":departuredate", trip.departureDate);
    qry.bindValue(":departuretime", trip.departureTime);
    qry.bindValue(":arrivaldate", trip.arrivalDate);
    qry.bindValue(":arrivaltime", trip.arrivalTime);
    qry.bindValue(":numpassengers", trip.numPassengers);
    qry.bindValue(":numstaffs", trip.numStaffs);
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

qint64 DbManager::getMaxBookingID(void)
{
    QSqlQuery qry;
    qint64 maxBookingId;

    qry.prepare("SELECT ifnull(MAX(bookingid), 0) FROM booking");

     if (qry.exec())
     {
        if (qry.next())
        {
            maxBookingId = qry.value(0).toLongLong();
        }
        return maxBookingId;
     }
     else
     {
       qDebug() << qry.lastError();
       /* There is some error, DIE here*/
     }
}

void DbManager::getAllBookingHistory(QList <QHash <QString, QString>>& allBookings)
{
    QSqlQuery qry;
    QHash <QString, QString> tempHash;

    qry.prepare("SELECT bookingid, bookingdate, bookingtime, mobilenumber "
                "FROM booking ORDER BY bookingid DESC");

     if (qry.exec())
     {
        while (qry.next())
        {
            QSqlQuery nameQry;
            QSqlQuery destinationQry;
            QSqlQuery profitQry;
            qint64 mobileNUmber;
            qint64 bookingId;

            bookingId = qry.value(0).toLongLong();
            tempHash["bookingid"] = qry.value(0).toString();
            tempHash["bookingdate"]= qry.value(1).toString();
            tempHash["bookingtime"]= qry.value(2).toString();
            mobileNUmber = qry.value(3).toLongLong();

            /*Query cutomer Name */
            nameQry.prepare("SELECT firstname, lastname FROM user "
                            "WHERE mobileno=:mobilenumber");
            nameQry.bindValue(":mobilenumber", mobileNUmber);
            if (nameQry.exec())
            {
               if (nameQry.next())
               {
                   tempHash["customername"] = nameQry.value(0).toString() + " " +
                                              nameQry.value(1).toString();
               }
            }
            else
            {
              qDebug()  << "user table querry failed" << qry.lastError();
              /* There is some error, DIE here*/
            }

            /*Query Destinations */
            destinationQry.prepare("SELECT destination FROM trip "
                            "WHERE bookingid = :bookingid");
            destinationQry.bindValue(":bookingid", bookingId);
            if (destinationQry.exec())
            {
               if (destinationQry.next())
               {
                   tempHash["destinations"] = destinationQry.value(0).toString();
               }
            }
            else
            {
              qDebug() << "trip table querry failed" << qry.lastError();
              /* There is some error, DIE here*/
            }

            /*Query profit*/
            profitQry.prepare("SELECT profit FROM expense "
                            "WHERE bookingid = :bookingid");
            profitQry.bindValue(":bookingid", bookingId);
            if (profitQry.exec())
            {
               if (profitQry.next())
               {
                   tempHash["profit"] = profitQry.value(0).toString();
               }
            }
            else
            {
              qDebug() << "expense table querry failed" << qry.lastError();
              /* There is some error, DIE here*/
            }

            /* Add the hash table to the list */
            allBookings.append(tempHash);
        }
     }
     else
     {
       qDebug() << "booking table querry failed" << qry.lastError();
       /* There is some error, DIE here*/
     }
}

void DbManager::_getExpense(DbExpense& expense, qint64 bookingId)
{
    QSqlQuery qry;

    qry.prepare("SELECT * FROM expense WHERE bookingid=:bookingid");
    qry.bindValue(":bookingid", bookingId);

    if (qry.exec())
    {
        qDebug( "fetched expense entry!");
        if (qry.next())
        {
            expense.bookingId = qry.value(0).toLongLong();
            expense.food = qry.value(1).toInt();
            expense.accomodation = qry.value(2).toInt();
            expense.transport = qry.value(3).toInt();
            expense.guideCharges = qry.value(4).toInt();
            expense.others = qry.value(5).toInt();
            expense.totalExpense = qry.value(6).toInt();
            expense.perHeadAmount = qry.value(7).toInt();
            expense.totalReturn = qry.value(8).toInt();
            expense.profit = qry.value(9).toInt();
        }
    }
    else
    {
        qDebug() << "Error getting expense entry" << qry.lastError();
    }
}

void DbManager::_getUser(DbUser& user, qint64 mobileNo)
{
    QSqlQuery qry;

    qry.prepare("SELECT * FROM user WHERE mobileno=:mobilenumber");
    qry.bindValue(":mobilenumber", mobileNo);

    if (qry.exec())
    {
        qDebug( "fetched user entry!");
        if (qry.next())
        {
            user.mobileNumber = qry.value(0).toLongLong();
            user.firstName = qry.value(1).toString();
            user.lastName = qry.value(2).toString();
            user.addressLine1 = qry.value(3).toString();
            user.addressLine2 = qry.value(4).toString();
            user.city = qry.value(5).toString();
            user.district = qry.value(6).toString();
            user.state = qry.value(7).toString();
            user.pinCode = qry.value(8).toInt();
        }
    }
    else
    {
        qDebug() << "Error getting user entry" << qry.lastError();
    }
}

void DbManager::_getBooking(DbBooking& booking, qint64 bookingId)
{

    QSqlQuery qry;

    qry.prepare("SELECT * FROM booking WHERE bookingid=:bookingid");
    qry.bindValue(":bookingid", bookingId);

    if (qry.exec())
    {
        qDebug( "fetched booking entry!");
        if (qry.next())
        {
            booking.bookingId = qry.value(0).toLongLong();
            booking.mobileNumber = qry.value(1).toLongLong();
            booking.adminName = qry.value(2).toString();
            booking.bookingDate = qry.value(3).toString();
            booking.bookingTime = qry.value(4).toString();
        }
    }
    else
    {
        qDebug() << "Error getting booking entry" << qry.lastError();
    }
}

void DbManager::_getTrip(DbTrip& trip, qint64 bookingId)
{
    QSqlQuery qry;

    qry.prepare("SELECT * FROM trip WHERE bookingid=:bookingid");
    qry.bindValue(":bookingid", bookingId);

    if (qry.exec())
    {
        qDebug( "fetched trip entry!");
        if (qry.next())
        {
            trip.bookingId = qry.value(0).toLongLong();
            trip.destination = qry.value(1).toString();
            trip.departureDate = qry.value(2).toString();
            trip.departureTime = qry.value(3).toString();
            trip.arrivalDate = qry.value(4).toString();
            trip.arrivalTime = qry.value(5).toString();
            trip.numPassengers = qry.value(6).toInt();
            trip.numStaffs = qry.value(7).toInt();
            trip.vehicle = qry.value(8).toString();
        }
    }
    else
    {
        qDebug() << "Error getting trip entry" << qry.lastError();
    }
}

void DbManager::getExpenseEntry(DbExpense& expense, qint64 bookingId)
{
    _getExpense(expense, bookingId);
}

void DbManager::getUserEntry(DbUser& user, qint64 mobileNo)
{
    _getUser(user, mobileNo);
}

void DbManager::getBookingEntry(DbBooking& booking, qint64 bookingId)
{
    _getBooking(booking, bookingId);
}

void DbManager::getTripEntry(DbTrip& trip, qint64 bookingId)
{
    _getTrip(trip, bookingId);
}
