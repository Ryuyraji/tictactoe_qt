#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QtSql/QSqlDatabase>

class DbManager
{
public:
    DbManager();
    bool addAccountInfo(const QString&, const QString&, const QString&);
    bool addWinPoint(const QString&);
    bool addLosePoint(const QString&);
    bool findAccountInfo(const QString&, const QString&);
    bool findUserID(const QString&);
    bool findUserNickname(const QString&);
    ~DbManager();
private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
