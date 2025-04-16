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
    Login(QWidget *parent = nullptr);
    ~Login();
    void make_account();
    void compare(); // id일치 불일치rememberCheck
    void setTitleShadow();
    bool getLoginState();
    void setLoginState(bool);
    static Login& instance();

signals:
    void goToCreateAccount();
    void returnToLobby();
    void login();
    void loginSucceed(QString);

private:
    Lobby *m_lobby;
    Ui::Login *login_ui;
    QString user_id;
    class QLineEdit *idInput;
    class QLineEdit *pwInput;
    bool loginState;
};
#endif // LOGIN_H
