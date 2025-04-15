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
    ui->setupUi(this);
    qDebug() << "hello" << "\n";
}

MyGame::~MyGame()
{
    delete myGame_ui;
}
