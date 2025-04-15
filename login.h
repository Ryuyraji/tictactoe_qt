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
class login;
}
QT_END_NAMESPACE

class login : public QWidget
{
    Q_OBJECT

public:
    login(QWidget *parent = nullptr);
    ~login();

private:
    Ui::login *loginui;

private:
    void make_account();
    void compare(); // id일치 불일치rememberCheck
private:
    QLineEdit *idinput;
    QLineEdit *pwinput;
    QByteArray data;
    QJsonArray users;


};
#endif // LOGIN_H
