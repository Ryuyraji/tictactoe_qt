#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QWidget>
#include <QJsonArray>

class QLineEdit;
class QPushButton;

QT_BEGIN_NAMESPACE
namespace Ui {
class Account;
}
QT_END_NAMESPACE


class Account : public QWidget
{
    Q_OBJECT

public:
    explicit Account(QWidget *parent = nullptr);
    ~Account();
    void setTitleShadow();
signals:
    void returnToLogin();
private:
    Ui::Account *account_ui;
    QLineEdit *editId;
    QLineEdit *editPw;
    QPushButton *createButton;

};

#endif // ACCOUNT_H
