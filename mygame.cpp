#include "mygame.h"
#include "setting.h"
#include "lobby.h"
#include "login.h"
#include "account.h"
#include <QStackedWidget>
#include <QVBoxLayout>

//enum WINDOWS { LOBBY, LOGIN, CREATE_ACCOUNT, INGAME, LEADERBOARDS, SETTING };
MyGame::MyGame(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(800, 800);
    stack = new QStackedWidget;
    Lobby *lobby_window = new Lobby;
    Login *login_window = new Login;
    Account *create_account_window = new Account;
    Setting *setting_window = new Setting;

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(stack);
    this->setLayout(layout);

    stack->addWidget(lobby_window);
    stack->addWidget(login_window);
    stack->addWidget(create_account_window);
    //stack->addWidget(game_window);
    //stack->addWidget(leaderboards_window);
    stack->addWidget(setting_window);
    stack->setCurrentIndex(0);

    connect(setting_window, &Setting::returnToLobby, this, [=](){
        stack->setCurrentIndex(LOBBY);
    });

    connect(lobby_window, &Lobby::goToLogin, this, [=](){
        stack->setCurrentIndex(LOGIN);
    });
    connect(login_window, &Login::returnToLobby, this, [=](){
        stack->setCurrentIndex(LOBBY);
    });

    connect(login_window, &Login::goToCreateAccount, this, [=](){
        stack->setCurrentIndex(CREATE_ACCOUNT);
    });

    connect(create_account_window, &Account::returnToLogin, this, [=](){
        stack->setCurrentIndex(LOGIN);
    });

    connect(lobby_window, &Lobby::goToSetting, this, [=](){
        stack->setCurrentIndex(3);
    });

    // connect(lobby_window, &Lobby::playGame, this, [=](){
    // stack->setCurrentIndex(INGAME);
    // });
    // connect(lobby_window, &Lobby::goToLeaderboards, this, [=](){
    // stack->setCurrentIndex(LEADERBOARDS);
    // });
    // connect(lobby_window, &Lobby::goToSetting, this, [=](){
    // stack->setCurrentIndex(SETTING);
    // });

    stack->show();}

MyGame::~MyGame() { }
