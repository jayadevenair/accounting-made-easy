#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QCoreApplication>
#include <QSqlDatabase>
#include <QString>
#include <QDateTime>

class DbExpense
{
public:
    qint64 bookingId;
    qint32 food;
    qint32 accomodation;
    qint32 transport;
    qint32 guideCharges;
    qint32 others;
    qint32 totalExpense;
    qint32 perHeadAmount;
    qint32 totalReturn;
    qint32 profit;
};

class DbTrip
{
public:
    qint64 bookingId;
    QString departureTime;
    QString departureDate;
    QString arrivalTime;
    QString arrivalDate;
    QString destination;
    QString vehicle;
    QString guideName;
    QString numPassengers;
    QString numStaffs;
};

class DbUser
{
public:
    QString firstName;
    QString lastName;
    QString addressLine1;
    QString addressLine2;
    QString city;
    QString district;
    QString state;
    QString pinCode;
    QString mobileNumber;
};

class DbBooking
{
public:
    QString currentDate;
    QString currentTime;
    QString adminName;
    qint64 bookingId;
    QString mobileNumber;
};

class DbManager
{
public:
    DbManager(const QString& path);
    ~DbManager();
    void createTables(void);
    void addExpenseEntry(const DbExpense& expense);
    void addUserEntry(const DbUser& user);
    void addBookingEntry(const DbBooking& booking);
    void addTripEntry(const DbTrip& trip);
private:
    void createTripTable(void);
    void createUserTable(void);
    void createBookingTable(void);
    void createExpenseTable(void);
    void _addExpense(const DbExpense& expense);
    void _addUser(const DbUser& user);
    void _addBooking(const DbBooking& booking);
    void _addTrip(const DbTrip& trip);
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
