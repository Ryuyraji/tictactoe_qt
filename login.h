#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QJsonArray>
#include "dbmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Login;
}
QT_END_NAMESPACE

class Login : public QWidget, protected DbManager
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();
private:
    Ui::Login *login_ui;

signals:
    void goToCreateAccount();
    void returnToLobby();

private:
    void make_account();
    void compare(); // id일치 불일치rememberCheck
private:
    class QLineEdit *idInput;
    class QLineEdit *pwInput;
    QByteArray data;
    QJsonArray users;
    class QPushButton *backBtn;


};
#endif // LOGIN_H
