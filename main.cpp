#include "login.h"
#include "account.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login w;
    //account v;
    w.show();
    //v.show();
    return a.exec();
}
