#include "mypage.h"
#include "ui_mypage.h"
#include "login.h"
#include "dbmanager.h"
#include <QMessageBox>
#include <QLineEdit>
#include <QPushButton>
#include <QInputDialog>
#include <QGraphicsDropShadowEffect>


MyPage::MyPage(QWidget *parent)
    :  QWidget(parent) ,myPage_ui(new Ui::MyPage)
{
    myPage_ui->setupUi(this);
    setTitleShadow();

    connect(myPage_ui->backBtn, &QPushButton::clicked, this, [=](){
        emit returnToLobby();
    });

    // 로그인 시 가져온 사용자 ID (로그인 후 저장된 userId)
    connect(&Login::instance(), &Login::loginSucceed, this, [&](QString userInfo){
        setUser(userInfo);
    });

    // 내 정보 가져오기
    DbManager::instance().fetchUserInfo();

    // 닉네임 수정 버튼 연결
    connect(myPage_ui->updateBtn, &QPushButton::clicked, this, [=]() {
        // 새 닉네임을 QInputDialog로 입력 받기
        while(1){
          bool ok;
          QString newNickname = QInputDialog::getText(this, "New NickName?", "Enter new nickname:", QLineEdit::Normal, "", &ok);

          if (ok && !newNickname.isEmpty()) {
              // 새 닉네임이 비어있지 않고, 입력이 성공적일 경우
              if(!DbManager::instance().findUserNickname(newNickname)){
                if (DbManager::instance().updateNickname(newNickname, userId)) {
                    // 수정된 닉네임을 UI에 표시
                    myPage_ui->nickname->setText(newNickname);
                    QMessageBox::information(this, "닉네임 수정", "닉네임이 성공적으로 수정되었습니다.");
                    break;
                }
                else{
                    QMessageBox::critical(this, "닉네임 수정", "닉네임 수정에 실패했습니다.");
                }
              }
              else {
                QMessageBox::critical(this, "닉네임 수정", "이미 사용중인 닉네임입니다.");
              }
          } else if (!ok) {
              // 사용자가 닉네임을 입력하지 않고 취소한 경우
              QMessageBox::warning(this, "닉네임 수정", "닉네임을 입력하지 않았습니다.");
              break;
          }
        }
    });

    // 계정 삭제 버튼 연결
    connect(myPage_ui->deleteBtn, &QPushButton::clicked, this, [=]() {
        // 계정 삭제 확인
        QMessageBox::StandardButton reply = QMessageBox::question(this, "계정 삭제", "정말로 계정을 삭제하시겠습니까?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            // 계정 삭제
            if (DbManager::instance().removeAccount(userId)) {
                QMessageBox::information(this, "삭제 완료", "계정이 삭제되었습니다.");
                m_lobby->getButton()->setText("Login");
                emit logout();
            } else {
                QMessageBox::critical(this, "계정 삭제", "계정 삭제에 실패했습니다.");
            }
        }
    });

    connect(myPage_ui->logoutBtn, &QPushButton::clicked, this, [=]() {
        myPage_ui->nickname->clear();
        myPage_ui->lossPointLabel->clear();
        myPage_ui->winPointLabel->clear();
        myPage_ui->account->clear();
        emit logout();
    });
}

void MyPage::setTitleShadow(){
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(12);
    shadow->setColor(QColor(0, 0, 0, 200));
    shadow->setOffset(7, 7);
    myPage_ui->title->setGraphicsEffect(shadow);
}

void MyPage::setUser(QString id){
        userId = id;
        userNickname = DbManager::instance().retrieveUserNickname(userId);
        QList userList = DbManager::instance().fetchUserInfo();
        QString win = "", loss = "";
        for(auto &it : userList){
            if(it[1] == userId){
                win = it[3];
                loss = it[4];
            }
        }
        myPage_ui->nickname->setText(userNickname);

        myPage_ui->winPointLabel->setText("Win: " + win);
        myPage_ui->lossPointLabel->setText("Loss: " + loss);
}

MyPage::~MyPage()
{
    delete myPage_ui;
}

