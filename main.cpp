#include "mygame.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyGame m;
    m.show();
    return a.exec();
}
