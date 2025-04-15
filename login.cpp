#include "login.h"
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFile>
#include <QIODevice>
#include <QByteArray>
#include <QJsonArray>
#include <QMessageBox>
#include <QFileDialog>
#include <QPushButton>

Login::Login(QWidget *parent)
    : QWidget(parent)
{
    // 전체 레이아웃
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);

    backBtn = new QPushButton(this);
    backBtn->setStyleSheet("QPushButton{"
                           "color:white;"
                           "background-color: rgba(0,0,0,148);"
                           "border:none;"
                           "}"
                           "QPushButton:hover{"
                           "background-color: rgb(190,190,190);"
                           "}"
                           "QPushButton:pressed{"
                           "background-color:rgb(170,170,170);"
                           "}"
                           );
    backBtn->setFixedSize(41,41);
    backBtn->move(30,30);
    mainLayout->addWidget(backBtn);
    connect(backBtn, &QPushButton::clicked, this, [=](){
        emit returnToLobby();
    });

    // "로그인" 텍스트
    QLabel *titleLabel = new QLabel("로그인");
    titleLabel->setStyleSheet("color:black;font-size: 20px; font-weight: bold;");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    mainLayout->addWidget(titleLabel);


    // ID 입력창
    idinput = new QLineEdit(this);
    idinput->setPlaceholderText("ID");
    idinput->setStyleSheet("color:black;padding: 10px; border-radius: 10px; background-color: #f0f0f0; border: none;");
    mainLayout->addWidget(idinput);

    // Password 입력창
    pwinput = new QLineEdit(this);
    pwinput->setPlaceholderText("Password");
    pwinput->setEchoMode(QLineEdit::Password);
    pwinput->setStyleSheet("color:black;padding: 10px; border-radius: 10px; background-color: #f0f0f0; border: none;");
    mainLayout->addWidget(pwinput);
    //뒤로가기 버튼



    QString inputFilePath = ("../../../../../db/user.json");
    // JSON 파일 로딩
    QFile file(inputFilePath);
    if (file.open(QIODevice::ReadOnly)) {
        QString data = file.readAll();
        file.close();
        QJsonDocument doc = QJsonDocument::fromJson(data.toLocal8Bit());
        QJsonObject Obj = doc.object();
        users = Obj["users"].toArray();
    }

    // Sign in 버튼
    QPushButton *loginButton = new QPushButton("Sign in", this);
    loginButton->setStyleSheet("color: blue;padding: 6px; background-color: #cce0ff; border: none; border-radius: 10px; font-weight: bold;");
    mainLayout->addWidget(loginButton);

    connect(loginButton, &QPushButton::clicked, this, [=]() {
        QString inputId = idinput->text();
        QString inputPw = pwinput->text();
        bool loginSuccess = false;

        for (auto userVal : users) {
            QJsonObject user = userVal.toObject();
            QString userId = user["id"].toString();
            QString userPw = user["password"].toString();
            if (inputId == userId && inputPw == userPw) {
                loginSuccess = true;
                break;
            }
        }

        if (loginSuccess) {
            QMessageBox::information(this, "로그인 성공", "환영합니다");
            emit returnToLobby();
        } else {
            QMessageBox::warning(this, "로그인 실패", "아이디 또는 비밀번호가 틀렸습니다.");
        }

});

    QPushButton *accountButton = new QPushButton("계정만들기", this);
    accountButton->setStyleSheet("color: blue;padding: 6px; background-color: #cce0ff; border: none; border-radius: 10px; font-weight: bold;");
    mainLayout->addWidget(accountButton);
    connect(accountButton, &QPushButton::clicked, this, [=](){
        emit goToCreateAccount();
    });

this->setLayout(mainLayout);
}


Login::~Login() {}
