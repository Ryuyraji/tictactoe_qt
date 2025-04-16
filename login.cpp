#include "login.h"
#include "dbmanager.h"
#include "ui_login.h"
#include "lobby.h"
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QInputDialog>
#include <QGraphicsDropShadowEffect>

Login::Login(QWidget *parent){}

Login::Login(Lobby *lobby, QWidget *parent)
    : m_lobby(lobby), QWidget(parent), login_ui(new Ui::Login)
{
    login_ui->setupUi(this);
    setTitleShadow();
    loginState = false;
    // 전체 레이아웃
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addStretch(1);

    // Centered widget container
    QWidget *centerWidget = new QWidget(this);
    QVBoxLayout *centerLayout = new QVBoxLayout(centerWidget);
    centerLayout->setSpacing(15);
    centerLayout->setAlignment(Qt::AlignCenter);

    connect(login_ui->backBtn, &QPushButton::clicked, this, [=](){
        emit returnToLobby();
    });

    // ID 입력창
    idInput = new QLineEdit(this);
    idInput->setPlaceholderText("ID");
    idInput->setStyleSheet("color:black;padding: 10px; border-radius: 10px; background-color: #f0f0f0; border: none;");
    idInput->setFixedSize(200,40);
    mainLayout->addWidget(idInput, 0, Qt::AlignCenter);

    // Password 입력창
    pwInput = new QLineEdit(this);
    pwInput->setPlaceholderText("Password");
    pwInput->setEchoMode(QLineEdit::Password);
    pwInput->setStyleSheet("color:black;padding: 10px; border-radius: 10px; background-color: #f0f0f0; border: none;");
    pwInput->setFixedSize(200,40);
    mainLayout->addWidget(pwInput, 0, Qt::AlignCenter);

    // Sign in 버튼
    QPushButton *loginButton = new QPushButton("Sign in", this);
    loginButton->setStyleSheet("color: blue;padding: 6px; background-color: #cce0ff; border: none; border-radius: 10px; font-weight: bold;");
    loginButton->setFixedSize(200,40);
    mainLayout->addWidget(loginButton, 0, Qt::AlignCenter);

    connect(loginButton, &QPushButton::clicked, this, [=]() {
        QString inputId = idInput->text();
        QString inputPw = pwInput->text();
        bool loginSuccess = false;

        if(DbManager::instance().findAccountInfo(inputId,inputPw)){
            loginSuccess = true;
        }
        if (loginSuccess) {
            QMessageBox::information(this, "로그인 성공", "환영합니다 " + inputId +"님!");
            user_id = inputId;
            idInput->clear();
            pwInput->clear();
            m_lobby->getButton()->setText("My Account");
            loginState = true;
            Login::instance().emit loginSucceed(user_id);
            emit returnToLobby();
        } else {
            QMessageBox::warning(this, "로그인 실패", "아이디 또는 비밀번호가 틀렸습니다.");
        }
    });

    QPushButton *accountButton = new QPushButton("Create an account", this);
    accountButton->setStyleSheet("color: blue;padding: 6px; background-color: #cce0ff; border: none; border-radius: 10px; font-weight: bold;");
    accountButton->setFixedSize(200,40);
    mainLayout->addWidget(accountButton, 0, Qt::AlignCenter);
    connect(accountButton, &QPushButton::clicked, this, [=](){
        idInput->clear();
        pwInput->clear();
        emit goToCreateAccount();
    });

    mainLayout->addWidget(centerWidget);
    mainLayout->addStretch(1);
}

void Login::setTitleShadow(){
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(12);
    shadow->setColor(QColor(0, 0, 0, 200));
    shadow->setOffset(7, 7);
    login_ui->title->setGraphicsEffect(shadow);
}

bool Login::getLoginState(){
    return loginState;
}

Login& Login::instance() {
    static Login _instance;
    return _instance;
}

QString Login::currentUser() const {
    return user_id;
}

Login::~Login() {}
