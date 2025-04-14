#include "mygame.h"
#include "./ui_mygame.h"

MyGame::MyGame(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyGame)
{
    ui->setupUi(this);
}

MyGame::~MyGame()
{
    delete ui;
}
