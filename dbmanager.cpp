#include "dbmanager.h"
#include <QLineEdit>
#include <QMessageBox>

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
    // for(int i = 0 ; i < 15; i++){
        // QString id = "jason" + QString::number(i);
        // QString pw = "123" + QString::number(i);
        // QString nickname = "jj" + QString::number(i);
        // QSqlQuery query(m_db);
        // query.prepare("INSERT INTO userTable (user_id, user_pw, user_nickname, winPoint, lossPoint) VALUES (:USER_ID, :USER_PW, :USER_NICKNAME, :WIN, :LOSS)");
        // query.bindValue(":USER_ID", id);
        // query.bindValue(":USER_PW", pw);
        // query.bindValue(":USER_NICKNAME", nickname);
        // query.bindValue(":WIN", i+2);
        // query.bindValue(":LOSS", i);
        // query.exec();
    // }
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

QStringList DbManager::fetchUserInfo() {
    QStringList userInfo;  // 반환할 데이터를 저장할 리스트

    QSqlQuery query(m_db);
    query.prepare("SELECT id, user_id, user_nickname, winPoint, lossPoint FROM userTable");

    if (!query.exec()) {
        qDebug() << "Query failed: " << query.lastError().text();
        return userInfo;  // 실패한 경우 빈 리스트 반환
    }

    while (query.next()) {
        // 쿼리 결과에서 값 추출하여 리스트에 저장
        userInfo << QString::number(query.value("id").toInt());
        userInfo << query.value("user_id").toString();
        userInfo << query.value("user_nickname").toString();
        userInfo << query.value("winPoint").toString();
        userInfo << query.value("lossPoint").toString();
    }

    return userInfo;  // 값을 담은 리스트 반환
}

bool DbManager::updateNickname(const QString& nickname, const QString& id) {

   //닉네임이 비어있으면
    if (nickname.isEmpty()) {
        QMessageBox::warning(nullptr, "닉네임 수정", "닉네임을 입력해주세요.");
        return false;
    }
    //수정
    QSqlQuery query(m_db);
    query.prepare("UPDATE userTable SET user_nickname = :nickname WHERE user_id = :user_id");
    query.bindValue(":nickname", nickname);
    query.bindValue(":user_id", id);  // 로그인한 사용자의 ID로 업데이트

    if (!query.exec()) {
        qDebug() << "Update failed: " << query.lastError().text();
        QMessageBox::critical(nullptr, "닉네임 수정", "닉네임 수정에 실패했습니다.");
        return false;  // 수정 실패 시
    }
    return true;
}



bool DbManager::removeAccount(const QString& id) {
        // 사용자에게 계정 삭제 여부 확인
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "계정 삭제", "정말로 계정을 삭제하시겠습니까?",
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            // 데이터베이스에서 계정 삭제
            QSqlQuery query(m_db);
            query.prepare("DELETE FROM userTable WHERE user_id = :user_id");
            query.bindValue(":user_id", id);  // 로그인한 사용자의 ID

            if (!query.exec()) {
                qDebug() << "Delete failed: " << query.lastError().text();
                QMessageBox::critical(nullptr, "계정 삭제", "계정 삭제에 실패했습니다.");
                return false;  // 실패 시
            }

            //삭제 후 반환
            QMessageBox::information(nullptr, "삭제 완료", "계정이 삭제되었습니다.");
            return true;  // 성공 시
        }

        return false;
    }


DbManager::~DbManager() {
    m_db.close();
}
