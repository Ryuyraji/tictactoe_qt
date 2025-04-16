#include "mygame.h"
#include "dbmanager.h"
#include "setting.h"
#include "lobby.h"
#include "login.h"
#include "account.h"
#include "tictactoe.h"
#include "mypage.h"
#include "leaderboards.h"
#include <QStackedWidget>
#include <QVBoxLayout>

// enum WINDOWS { LOBBY, LOGIN, CREATE_ACCOUNT, MYPAGE, INGAME, LEADERBOARDS, SETTING };
MyGame::MyGame(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(850, 850);
    stack = new QStackedWidget;
    // need QVBoxLayout to show the QStackedWidget
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(stack);
    this->setLayout(layout);

    // stack all the widgets that we made onto QStacked Widget
    Lobby *lobby_window = new Lobby;
    stack->addWidget(lobby_window);

    Login *login_window = new Login(lobby_window);
    stack->addWidget(login_window);

    Account *create_account_window = new Account;
    stack->addWidget(create_account_window);

    MyPage *myPage_window = new MyPage(lobby_window);
    stack->addWidget(myPage_window);

    Tictactoe *game_window = new Tictactoe;
    stack->addWidget(game_window);

    Leaderboards *leaderboards_window = new Leaderboards;
    stack->addWidget(leaderboards_window);

    Setting *setting_window = new Setting;
    stack->addWidget(setting_window);

    // set the current window as main lobby
    stack->setCurrentIndex(LOBBY);

    // signals & slots for each buttons
    connect(lobby_window, &Lobby::goToLogin, this, [=](){
        if(login_window->getLoginState()){
            stack->setCurrentIndex(MYPAGE);
        }
        else{
            stack->setCurrentIndex(LOGIN);
        }
    });

    connect(login_window, &Login::login, this, [=](){
        lobby_window->setLoginButton();
        stack->setCurrentIndex(LOBBY);
    });

    connect(myPage_window, &MyPage::logout, this, [=](){
        login_window->setLoginState(false);
        lobby_window->setAccountButton();
        game_window->resetUser();
        stack->setCurrentIndex(LOBBY);
    });

    connect(myPage_window, &MyPage::returnToLobby, this, [=](){
        stack->setCurrentIndex(LOBBY);
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

    connect(lobby_window, &Lobby::playGame, this, [=](){
        setting_window->stopMusic();
        stack->setCurrentIndex(INGAME);
    });
    connect(lobby_window, &Lobby::goToLeaderboards, this, [=](){
        stack->setCurrentIndex(LEADERBOARDS);
    });
    connect(lobby_window, &Lobby::goToSetting, this, [=](){
        stack->setCurrentIndex(SETTING);
    });

    connect(game_window, &Tictactoe::returnToLobby, this, [=](){
        setting_window->playMusic();
        stack->setCurrentIndex(LOBBY);
    });

    connect(game_window, &Tictactoe::winGame, this, [=](QString id){
        myPage_window->setUser(id);
        leaderboards_window->setUserLeaderboard();
    });

    connect(game_window, &Tictactoe::loseGame, this, [=](QString id){
        myPage_window->setUser(id);
        leaderboards_window->setUserLeaderboard();
    });

    connect(leaderboards_window, &Leaderboards::returnToLobby, this, [=](){
        stack->setCurrentIndex(LOBBY);
    });
    connect(setting_window, &Setting::returnToLobby, this, [=](){
        stack->setCurrentIndex(LOBBY);
    });




    stack->show();
}

MyGame::~MyGame() { }
