#ifndef MYPAGE_H
#define MYPAGE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class MyPage;
}

class MyPage : public QWidget
{
    Q_OBJECT

public:
    explicit MyPage(QWidget *parent = nullptr);
    ~MyPage();

signals:
    void logout();
private:
    Ui::MyPage *ui;
    QString userId;  // 로그인한 사용자의 ID
    QString userNickname;  // 로그인한 사용자의 닉네임
    QString newNickname;
    QPushButton updateBtn;
    QPushButton deleteBtn;
    QPushButton logoutBtn;

};

#endif // MYPAGE_H
