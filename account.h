#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QWidget>
#include <QJsonArray>
#include "dbmanager.h"

class QLineEdit;
class QPushButton;

class Account : public QWidget, protected DbManager
{
    Q_OBJECT

public:
    explicit Account(QWidget *parent = nullptr);
    ~Account();
signals:
    void returnToLogin();
private:
    QLineEdit *editId;
    QLineEdit *editPw;
    QPushButton *createButton;
    QJsonArray users1;
    QPushButton *backBtn;

};

#endif // ACCOUNT_H
