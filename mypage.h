#ifndef MYPAGE_H
#define MYPAGE_H

#include <QString>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
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

private:
    Ui::MyPage *ui;
private slots:

    void updateNickname();
    void removeAccount();

private:
    QString userId;
    QLabel *winLabel;
    QLabel *loseLabel;
    QPushButton *deleteBtn;
    QPushButton *updateBtn;
    QLabel *nicknameEdit;


};


#endif // MYPAGE_H
