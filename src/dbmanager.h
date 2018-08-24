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
    qint16 numPassengers;
    qint16 numStaffs;
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
    qint32 pinCode;
    qint64 mobileNumber;
};

class DbBooking
{
public:
    QString bookingDate;
    QString bookingTime;
    QString adminName;
    qint64 bookingId;
    qint64 mobileNumber;
};

class DbManager
{
public:
    DbManager(const QString& path);
    ~DbManager();
    void createTables(void);
    static void addExpenseEntry(const DbExpense& expense);
    static void addUserEntry(const DbUser& user);
    static void addBookingEntry(const DbBooking& booking);
    static void addTripEntry(const DbTrip& trip);
    static qint64 getMaxBookingID(void);
    static void getAllBookingHistory(QList <QHash <QString, QString>>& allBookings);
private:
    void createTripTable(void);
    void createUserTable(void);
    void createBookingTable(void);
    void createExpenseTable(void);
    static void _addExpense(const DbExpense& expense);
    static void _addUser(const DbUser& user);
    static void _addBooking(const DbBooking& booking);
    static void _addTrip(const DbTrip& trip);
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
