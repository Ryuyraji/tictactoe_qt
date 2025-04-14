#include "mygame.h"

#include <QApplication>
#include <QLabel>
#include <QPixmap>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyGame m;
    m.show();
    return a.exec();
}
