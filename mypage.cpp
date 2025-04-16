
#include "mypage.h"
#include "ui_mypage.h"
#include "login.h"
#include "dbmanager.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QLineEdit>
#include <QPushButton>
#include <QInputDialog>

MyPage::MyPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyPage)
{
    ui->setupUi(this);

    // 로그인 시 가져온 사용자 ID (로그인 후 저장된 userId)
    connect(&Login::instance(), &Login::loginSucceed, this, [&](QString userInfo){
        userId = userInfo;
        userNickname = DbManager::instance().retrieveUserNickname(userId);
        qDebug() << "MyPage: " << userNickname << "\n";
        ui->nickname->setText(userNickname);
    });

    // 내 정보 가져오기
    DbManager::instance().fetchUserInfo();

    // 닉네임 수정 버튼 연결
    connect(ui->updateBtn, &QPushButton::clicked, this, [=]() {
        // 새 닉네임을 QInputDialog로 입력 받기
        bool ok;
        QString newNickname = QInputDialog::getText(this, "New NickName?", "Enter new nickname:", QLineEdit::Normal, "", &ok);

        if (ok && !newNickname.isEmpty()) {
            // 새 닉네임이 비어있지 않고, 입력이 성공적일 경우
            if (DbManager::instance().updateNickname(newNickname, userId)) {
                // 수정된 닉네임을 UI에 표시
                ui->nickname->setText(newNickname);
                QMessageBox::information(this, "닉네임 수정", "닉네임이 성공적으로 수정되었습니다.");
            } else {
                QMessageBox::critical(this, "닉네임 수정", "닉네임 수정에 실패했습니다.");
            }
        } else if (ok) {
            // 사용자가 닉네임을 입력하지 않고 취소한 경우
            QMessageBox::warning(this, "닉네임 수정", "닉네임을 입력하지 않았습니다.");
        }
    });

    // 계정 삭제 버튼 연결
    connect(ui->deleteBtn, &QPushButton::clicked, this, [=]() {
        // 계정 삭제 확인
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "계정 삭제", "정말로 계정을 삭제하시겠습니까?", QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            // 계정 삭제
            if (DbManager::instance().removeAccount(userId)) {
                QMessageBox::information(this, "삭제 완료", "계정이 삭제되었습니다.");
                emit logout();
            } else {
                QMessageBox::critical(this, "계정 삭제", "계정 삭제에 실패했습니다.");
            }
        }
    });


    connect(ui->logoutBtn, &QPushButton::clicked, this, [=]() {
        emit logout();
    });
}

MyPage::~MyPage()
{
    delete ui;
}

