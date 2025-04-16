#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class DbManager
{
public:
    QString getConnectionName() const;
    void setConnectionName(const QString&);
    bool addAccountInfo(const QString&, const QString&, const QString&);
    bool addWinPoint(const QString&);
    bool addLossPoint(const QString&);
    bool findAccountInfo(const QString&, const QString&);
    bool findUserID(const QString&);
    bool findUserNickname(const QString&);
    static DbManager& instance();
    QSqlDatabase& getDatabase();
    QStringList fetchUserInfo(const QString&, const QString&, const QString&);//정보 가져오기
    bool updateNickname(const QString&,const QString&);
    bool removeAccount(const QString&, const QString&, const QString&);
private:
    DbManager();
    ~DbManager();
    QSqlDatabase m_db;
    QString db_connectionName;
};

#endif // DBMANAGER_H
