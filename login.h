#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QJsonDocument>
#include <QJsonObject>
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
private:
    Ui::Login *login_ui;

signals:
    void goToCreateAccount();
    void returnToLobby();

private:
    void make_account();
    void compare(); // id일치 불일치rememberCheck
private:
    QLineEdit *idinput;
    QLineEdit *pwinput;
    QByteArray data;
    QJsonArray users;
    QPushButton *backBtn;


};
#endif // LOGIN_H
