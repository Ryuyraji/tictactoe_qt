#include "mygame.h"
#include "setting.h"
#include "lobby.h"
#include "./ui_mygame.h"
#include <QStackedWidget>
#include <QVBoxLayout>

MyGame::MyGame(QWidget *parent)
    : QWidget(parent)
    , myGame_ui(new Ui::MyGame)
{
    myGame_ui->setupUi(this);
    this->setFixedSize(800, 800);
    stack = new QStackedWidget;
    Lobby *lobby_window = new Lobby;
    Setting *setting_window = new Setting;

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(stack);
    this->setLayout(layout);

    stack->addWidget(lobby_window);
    //stack->addWidget(login_window);
    //stack->addWidget(game_window);
    //stack->addWidget(leaderboards_window);
    stack->addWidget(setting_window);
    stack->setCurrentIndex(0);
    connect(setting_window, &Setting::returnToLobby, this, [=](){
        stack->setCurrentIndex(LOBBY);
    });
    connect(lobby_window, &Lobby::goToSetting, this, [=](){
        stack->setCurrentIndex(1);
    });

    // connect(setting_window, &Setting::returnToLobby, this, [=](){
        // stack->setCurrentIndex(LOBBY);
    // });
    // connect(lobby_window, &Lobby::goToLogin, this, [=](){
        // stack->setCurrentIndex(LOGIN);
    // });
    // connect(lobby_window, &Lobby::playGame, this, [=](){
        // stack->setCurrentIndex(INGAME);
    // });
    // connect(lobby_window, &Lobby::goToLeaderboards, this, [=](){
        // stack->setCurrentIndex(LEADERBOARDS);
    // });
    // connect(lobby_window, &Lobby::goToSetting, this, [=](){
        // stack->setCurrentIndex(SETTING);
    // });

    stack->show();
}

MyGame::~MyGame()
{
    delete myGame_ui;
}
