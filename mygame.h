#ifndef MYGAME_H
#define MYGAME_H

#include <QWidget>

enum WINDOWS { LOBBY, LOGIN, CREATE_ACCOUNT, INGAME, LEADERBOARDS, SETTING };

class MyGame : public QWidget
{
    Q_OBJECT

public:
    MyGame(QWidget *parent = nullptr);
    ~MyGame();

private:
    class QStackedWidget *stack;
};
#endif // MYGAME_H
