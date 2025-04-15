#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "lobby.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Login;
}
QT_END_NAMESPACE

class Login : public QWidget
{
    Q_OBJECT

public:
    Login(Lobby *lobby, QWidget *parent = nullptr);
    ~Login();
    void make_account();
    void compare(); // id일치 불일치rememberCheck
    void setTitleShadow();

signals:
    void goToCreateAccount();
    void returnToLobby();
    void loginSucceed();

private:
    Lobby *m_lobby;
    Ui::Login *login_ui;
    QString user_id;
    class QLineEdit *idInput;
    class QLineEdit *pwInput;
};
#endif // LOGIN_H
