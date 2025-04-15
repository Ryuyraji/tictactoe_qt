#include "mypage.h"
#include "ui_mypage.h"
#include "dbmanager.h"
#include <QPushButton>
#include <QMessageBox>

MyPage::MyPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyPage)
{
    ui->setupUi(this);

    // QSqlQuery query(DbManager::instance().getDatabase());
    // query.prepare("SELECT user_id, user_nickname, winPoint, lossPoint, FROM userTable");
    // if(!query.exec()){
    //     qDebug() << "Query failed\n";
    //     return;
    // }

    // while(query.next()){
    //     QString userId = query.value("user_id").toString();
    //     QString userNickname = query.value("user_nickname").toString();
    //     int win = query.value("winPoint").toInt();
    //     int loss = query.value("lossPoint").toInt();
    // }

    connect(ui->updateBtn, &QPushButton::clicked, this, &MyPage::updateNickname);
    connect(ui->deleteBtn, &QPushButton::clicked, this, &MyPage::removeAccount);
}



void MyPage::updateNickname(){


    QString newNickname = ui->nicknameEdit->text();

    if (newNickname.isEmpty()) {
        QMessageBox::warning(this, "닉네임 수정", "닉네임을 입력해주세요.");
        return;
    }

    // 데이터베이스에 닉네임 수정
    QSqlQuery query(DbManager::instance().getDatabase());
    query.prepare("UPDATE userTable SET user_nickname = :nickname WHERE user_id = :user_id");
    query.bindValue(":nickname", newNickname);
    query.bindValue(":user_id", userId);  // 로그인한 사용자의 ID로 업데이트

    if (!query.exec()) {
        qDebug() << "Update failed: " << query.lastError().text();
        QMessageBox::critical(this, "닉네임 수정", "닉네임 수정에 실패했습니다.");
        return;
    }

    QMessageBox::information(this, "닉네임 수정", "닉네임이 수정되었습니다.");
    newNickname = newNickname;
}


void MyPage::removeAccount() {
    // 계정 삭제 확인
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "계정 삭제", "정말로 계정을 삭제하시겠습니까?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // 데이터베이스에서 계정 삭제
        QSqlQuery query(DbManager::instance().getDatabase());
        query.prepare("DELETE FROM userTable WHERE user_id = :user_id");
        query.bindValue(":user_id", "user_id_value");  // 실제 사용자의 ID 값으로 교체해야 함

        if (!query.exec()) {
            // 삭제 실패 시 오류 처리
            qDebug() << "Delete failed: " << query.lastError().text();
            QMessageBox::critical(this, "계정 삭제", "계정 삭제에 실패했습니다.");
            return;
        }

        // 삭제 완료 시 사용자에게 알림
        QMessageBox::information(this, "삭제 완료", "계정이 삭제되었습니다.");


    }
}

MyPage::~MyPage()
{
    delete ui;
}
