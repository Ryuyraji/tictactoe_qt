#include "mygame.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyGame g;
    g.show();
    return a.exec();
}
