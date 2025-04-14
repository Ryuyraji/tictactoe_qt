#ifndef MYGAME_H
#define MYGAME_H

#include <QWidget>

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
    Ui::MyGame *ui;
};
#endif // MYGAME_H
