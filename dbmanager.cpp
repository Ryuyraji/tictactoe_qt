#include "dbmanager.h"

DbManager::DbManager() {
    const QString connectionName = "MyGameDB";
    setConnectionName(connectionName);
    if (QSqlDatabase::contains(connectionName)) {
        m_db = QSqlDatabase::database(connectionName);
        if (!m_db.isOpen() && !m_db.open()) {
            qDebug() << "Reused DB connection failed to open";
        }
    } else {
        m_db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
        m_db.setDatabaseName("./userDB.sqlite");
        if (!m_db.open()) {
            qDebug() << "Error: connection with database failed";
        } else {
            qDebug() << "Database: connection ok!";
        QString query =
            "CREATE TABLE IF NOT EXISTS userTable ("
            "id integer PRIMARY KEY AUTOINCREMENT,"
            "user_id VARCHAR(30),"
            "user_pw VARCHAR(30),"
            "user_nickname VARCHAR(30),"
            "winPoint int,"
            "lossPoint int);";

        QSqlQuery qry(m_db);
        if (!qry.exec(query)) {
            qDebug() << "Creating the table failed:" << qry.lastError();
        } else {
            qDebug() << "Successfully created!";
        }
      }
    }
}
bool DbManager::addAccountInfo(const QString& id, const QString& pw, const QString& nickname){
    bool success = false;

    QSqlQuery query(m_db);
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
        qDebug() << "addAccountInfo error:" << query.lastError();
    }
    return success;
}

bool DbManager::addWinPoint(const QString &id){
    bool success = false;
    QSqlQuery query(m_db);
    query.prepare("UPDATE userTable SET winPoint = winPoint + 1 WHERE user_id = :USER_ID");
    query.bindValue(":USER_ID", id);
    if(query.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "addWinPoint error:" << query.lastError();
    }
    return success;
}

bool DbManager::addLossPoint(const QString &id){
    bool success = false;
    QSqlQuery query(m_db);
    query.prepare("UPDATE userTable SET lossPoint = lossPoint + 1 WHERE user_id = :USER_ID");
    query.bindValue(":USER_ID", id);
    if(query.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "addLossPoint error:" << query.lastError();
    }
    return success;
}

bool DbManager::findAccountInfo(const QString& id, const QString& pw){
    bool success = false;
    QSqlQuery query(m_db);
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
    QSqlQuery query(m_db);
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
    QSqlQuery query(m_db);
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

QString DbManager::getConnectionName() const{
    return db_connectionName;
}
void DbManager::setConnectionName(const QString& custom_connection){
    db_connectionName = custom_connection;
}

DbManager& DbManager::instance() {
    static DbManager instance;
    return instance;
}

QSqlDatabase& DbManager::getDatabase(){
    return m_db;
}

DbManager::~DbManager() {
    m_db.close();
}
