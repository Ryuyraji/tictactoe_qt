#include <QJsonArray>


#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QWidget>

class QLineEdit;
class QPushButton;

class account : public QWidget
{
    Q_OBJECT

public:
    explicit account(QWidget *parent = nullptr);
    ~account();

private:
    QLineEdit *editId;
    QLineEdit *editPw;
    QPushButton *createButton;
    QJsonArray users1;


};

#endif // ACCOUNT_H
