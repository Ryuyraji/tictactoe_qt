#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QJsonArray>

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

signals:
    void goToCreateAccount();
    void returnToLobby();

private:
    Ui::Login *login_ui;
    QString user_id;
    class QLineEdit *idInput;
    class QLineEdit *pwInput;
    QByteArray data;
    QJsonArray users;
    class QPushButton *backBtn;
};
#endif // LOGIN_H
