#include "dbmanager.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

DbManager::DbManager() {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("./userDB.sqlite");
    if (!m_db.open()){
        qDebug() << "Error: connection with database failed";
    }
    else{
        qDebug() << "Database: connection ok";
    }
    QString query = "CREATE TABLE IF NOT EXISTS userTable ("
                    "id integer PRIMARY KEY AUTOINCREMENT,"
                    "user_id VARCHAR(30),"
                    "user_pw VARCHAR(30),"
                    "user_nickname VARCHAR(30),"
                    "winPoint int,"
                    "lossPoint int);";

    QSqlQuery qry;
    if(!qry.exec(query)){
        qDebug() << "Creating the table failed\n";
    }
    else{
        qDebug() << "successfully created!\n";
    }
}

bool DbManager::addAccountInfo(const QString& id, const QString& pw, const QString& nickname){
    bool success = false;

    QSqlQuery query;
    query.prepare("INSERT INTO userTable (user_id, user_pw, user_nickname, winPoint, lossPoint) VALUES (:USER_ID, :USER_PW, :USER_NICKNAME, :WIN, :LOSS)");
    query.bindValue(":USER_ID", id);
    query.bindValue(":USER_PW", pw);
    query.bindValue(":USER_NICKNAME", nickname);
    query.bindValue(":WIN", 0);
    query.bindValue(":LOSS", 0);

    if(query.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "addID error:" << query.lastError();
    }
    return success;
}

bool DbManager::addWinPoint(const QString &id){
    bool success = false;
    QSqlQuery query;
    query.prepare("UPDATE userTable SET winPoint = winPoint + 1 WHERE user_id = :USER_ID");
    query.bindValue(":USER_ID", id);
    if(query.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "addScore error:" << query.lastError();
    }
    return success;
}

bool DbManager::addLosePoint(const QString &id){
    bool success = false;
    QSqlQuery query;
    query.prepare("UPDATE userTable SET lossPoint = lossPoint + 1 WHERE user_id = :USER_ID");
    query.bindValue(":USER_ID", id);
    if(query.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "addScore error:" << query.lastError();
    }
    return success;
}

bool DbManager::findAccountInfo(const QString& id, const QString& pw){
    bool success = false;
    QSqlQuery query;
    query.prepare("SELECT * FROM userTable WHERE user_id=:USER_ID and user_pw=:USER_PW");
    query.bindValue(":USER_ID", id);
    query.bindValue(":USER_PW", pw);
    if(query.exec()){
        if (query.next()) {
            success = true;
        }
        else {
            qDebug() << "User not found\n";
        }
    }
    return success;
}

bool DbManager::findUserID(const QString& id){
    bool success = false;
    QSqlQuery query;
    query.prepare("SELECT * FROM userTable WHERE user_id=:USER_ID");
    query.bindValue(":USER_ID", id);
    if(query.exec()){
        if (query.next()) {
            success = true;
        }
        else {
            qDebug() << "findAccountInfo query error:" << query.lastError();
        }
    }
    else{
        qDebug() << "User ID not found\n";
    }
    return success;
}

bool DbManager::findUserNickname(const QString& nickname){
    bool success = false;
    QSqlQuery query;
    query.prepare("SELECT * FROM userTable WHERE user_nickname=:USER_NICKNAME");
    query.bindValue(":USER_NICKNAME", nickname);
    if(query.exec()){
        if (query.next()) {
            success = true;
        }
        else {
            qDebug() << "findAccountInfo query error:" << query.lastError();
        }
    }
    else{
        qDebug() << "User ID not found\n";
    }
    return success;
}

DbManager::~DbManager() {}
