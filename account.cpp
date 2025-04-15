#include "account.h"
#include "dbmanager.h"
#include "ui_account.h"
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QRegularExpression>
#include <QInputDialog>
#include <QGraphicsDropShadowEffect>

Account::Account(QWidget *parent)
    : QWidget(parent), account_ui(new Ui::Account)
{
    account_ui->setupUi(this);
    setTitleShadow();

    // 전체 레이아웃
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addStretch(1);

    QWidget *centerWidget = new QWidget(this);
    QVBoxLayout *centerLayout = new QVBoxLayout(centerWidget);
    centerLayout->setSpacing(15);
    centerLayout->setAlignment(Qt::AlignCenter);

    connect(account_ui->backBtn, &QPushButton::clicked, this, [=](){
        emit returnToLogin();
    });

    // 아이디
    editId = new QLineEdit(this);
    editId->setPlaceholderText("New ID");
    editId->setStyleSheet("color:black;padding: 10px; border-radius: 10px; background-color: #f0f0f0; border: none;");
    editId->setFixedSize(200,40);
    mainLayout->addWidget(editId, 0, Qt::AlignCenter);

    // 비밀번호
    editPw = new QLineEdit(this);
    editPw->setEchoMode(QLineEdit::Password);
    editPw->setPlaceholderText("New Password");
    editPw->setStatusTip("at least 6 letters containing A-Z,a-z,!@#$%^&*()_+-=[];';:,./");
    editPw->setStyleSheet("color:black;padding: 10px; border-radius: 10px; background-color: #f0f0f0; border: none;");
    editPw->setFixedSize(200,40);
    mainLayout->addWidget(editPw,0,Qt::AlignCenter);

    // 계정 생성 버튼
    createButton = new QPushButton("Create", this);
    createButton->setStyleSheet("color: blue;padding: 6px; background-color: #cce0ff; border: none; border-radius: 10px; font-weight: bold;");
    createButton->setFixedSize(200,40);
    mainLayout->addWidget(createButton, 0, Qt::AlignCenter);

    //계정 버튼 누를떄
    connect(createButton, &QPushButton::clicked, this, [=]() {
        QString makeId = editId->text();
        QString makePw = editPw->text();
        QString makeNickname = "";
        bool accountAvailable = false;
        bool nickName;

            //이미 계정이 있는 경우
            QRegularExpression regex("^(?=.*[A-Za-z])(?=.*\\d)(?=.*[!@#$%^&*()_+=-]).{6,}$");
            if (DbManager::instance().findUserID(makeId)) {
                QMessageBox::warning(this, "중복된 아이디", "이미 계정이 있습니다.");
            }
            //비밀번호 생성오류
            else if (!regex.match(makePw).hasMatch()) {
                QMessageBox::warning(this, "비밀번호 오류", "비밀번호는 6자 이상이며, 영어/숫자/특수문자를 포함해야 합니다.");
            }
            else{
                while(1){
                    makeNickname = QInputDialog::getText(this, "NickName?", "Enter any nickname!", QLineEdit::Normal, "", &nickName);
                    if(nickName == false){
                        editId->clear();
                        editPw->clear();
                        emit returnToLogin();
                        break;
                    }
                    if(DbManager::instance().findUserNickname(makeNickname) || makeNickname == ""){
                        QMessageBox::information(this, "Failed", "Cannot use this Nickname, Try again!");
                    }
                    else{
                        accountAvailable = true;
                        editId->clear();
                        editPw->clear();
                        break;
                    }
                }
            }
            if(accountAvailable){
                if(DbManager::instance().addAccountInfo(makeId, makePw, makeNickname)){
                    QMessageBox::information(this, "성공", "계정이 추가되었습니다!");
                    emit returnToLogin();
                }
            }
    });
    mainLayout->addWidget(centerWidget);
    mainLayout->addStretch(1);
}

void Account::setTitleShadow(){
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(12);
    shadow->setColor(QColor(0, 0, 0, 200));
    shadow->setOffset(7, 7);
    account_ui->title->setGraphicsEffect(shadow);
}

Account::~Account() {}


