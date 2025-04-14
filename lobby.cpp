#include "lobby.h"
#include "ui_lobby.h"
#include <QPalette>
#include <QPixmap>

Lobby::Lobby(QWidget *parent)
    : QWidget(parent)
    , lobby_ui(new Ui::lobby)
{
    lobby_ui->setupUi(this);
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

Lobby::~Lobby()
{
    delete lobby_ui;
}
