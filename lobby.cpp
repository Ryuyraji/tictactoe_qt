#include "lobby.h"
#include "ui_lobby.h"
#include <QGraphicsDropShadowEffect>

Lobby::Lobby(QWidget *parent)
    : QWidget(parent)
    , lobby_ui(new Ui::lobby)
{
    lobby_ui->setupUi(this);
    setTitleShadow();

    connect(lobby_ui->loginBtn, &QPushButton::clicked, this, [=](){
        emit goToLogin();
    });
    connect(lobby_ui->gameStartBtn, &QPushButton::clicked, this, [=](){
        emit playGame();
    });
    connect(lobby_ui->leaderboardsBtn, &QPushButton::clicked, this, [=](){
        emit goToLeaderboards();
    });
    connect(lobby_ui->settingBtn, &QPushButton::clicked, this, [=](){
        emit goToSetting();
    });
    connect(lobby_ui->quitBtn, &QPushButton::clicked, this, [=](){
        qApp->quit();
    });
}

void Lobby::setTitleShadow(){
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(12);                // how soft the shadow is
    shadow->setColor(QColor(0, 0, 0, 200));  // shadow color and transparency
    shadow->setOffset(7, 7);                 // offset (x, y)
    lobby_ui->title->setGraphicsEffect(shadow);
}

QPushButton *Lobby::getButton(){
    return lobby_ui->loginBtn;
}

void Lobby::setLoginButton(){
    lobby_ui->loginBtn->setText("My Account");
}

void Lobby::setAccountButton(){
    lobby_ui->loginBtn->setText("Login");
}

Lobby::~Lobby()
{
    delete lobby_ui;
}
