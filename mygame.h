#ifndef MYGAME_H
#define MYGAME_H

#include <QWidget>

enum WINDOWS { LOBBY, LOGIN, INGAME, SETTING, ABOUT };

QT_BEGIN_NAMESPACE
namespace Ui {
class MyGame;
}
QT_END_NAMESPACE

class MyGame : public QWidget
{
    Q_OBJECT

public:
    MyGame(QWidget *parent = nullptr);
    ~MyGame();

private:
    Ui::MyGame *myGame_ui;
    class QStackedWidget *stack;
};
#endif // MYGAME_H
