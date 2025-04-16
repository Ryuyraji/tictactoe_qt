#ifndef MYPAGE_H
#define MYPAGE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "lobby.h"

namespace Ui {
class MyPage;
}

class MyPage : public QWidget
{
    Q_OBJECT

public:
    MyPage(QWidget *parent = nullptr);
    void setTitleShadow();
    void setUser(QString);
    ~MyPage();

signals:
    void logout();
    void returnToLobby();
private:
    Ui::MyPage *myPage_ui;
    Lobby *m_lobby;
    QString userId;  // 로그인한 사용자의 ID
    QString userNickname;  // 로그인한 사용자의 닉네임
    QString newNickname;
    QPushButton updateBtn;
    QPushButton deleteBtn;
    QPushButton logoutBtn;

};

#endif // MYPAGE_H
