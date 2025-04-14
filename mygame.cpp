#include "mygame.h"
#include "./ui_mygame.h"

MyGame::MyGame(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyGame)
{
    ui->setupUi(this);
    qDebug() << "hello" << "\n";
}

MyGame::~MyGame()
{
    delete ui;
}
