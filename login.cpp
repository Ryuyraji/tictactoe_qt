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

login::login(QWidget *parent)
    : QWidget(parent)
{
    // 전체 레이아웃
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);

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


    QString inputFilePath = ("/Users/yj/veda_qt/user.json");
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
        } else {
            QMessageBox::warning(this, "로그인 실패", "아이디 또는 비밀번호가 틀렸습니다.");
        }

});

    QPushButton *accountButton = new QPushButton("계정만들기", this);
    accountButton->setStyleSheet("color: blue;padding: 6px; background-color: #cce0ff; border: none; border-radius: 10px; font-weight: bold;");
    mainLayout->addWidget(accountButton);

this->setLayout(mainLayout);
}


login::~login() {}
