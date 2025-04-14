#include "mygame.h"
#include "./ui_mygame.h"
#include <QStackedWidget>
#include "setting.h"
#include <QVBoxLayout>

MyGame::MyGame(QWidget *parent)
    : QWidget(parent)
    , myGame_ui(new Ui::MyGame)
{
    myGame_ui->setupUi(this);
    this->setFixedSize(800, 800);
    stack = new QStackedWidget;
    Setting *setting_window = new Setting;

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(stack);
    this->setLayout(layout);

    //stack->addWidget(lobby_window);
    //stack->addWidget(login_window);
    //stack->addWidget(game_window);
    stack->addWidget(setting_window);
    stack->setCurrentIndex(0);

    // connect(setting_window, &Setting::returnToLobby, this, [=](){
        // stack->setCurrentIndex(0);
    // });

    stack->show();
}

MyGame::~MyGame()
{
    delete myGame_ui;
}
