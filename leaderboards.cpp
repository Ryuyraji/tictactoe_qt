#include "leaderboards.h"
#include "ui_leaderboards.h"
#include "dbmanager.h"
#include <QGraphicsDropShadowEffect>

Leaderboards::Leaderboards(QWidget *parent)
    : QWidget(parent)
    , leaderboard_ui(new Ui::leaderboards)
{
    leaderboard_ui->setupUi(this);
    setTitleShadow();

    connect(leaderboard_ui->backBtn, &QPushButton::clicked, this, [=](){
        emit returnToLobby();
    });

    QSqlQuery query(DbManager::instance().getDatabase());
    query.prepare("SELECT id, user_nickname, winPoint, lossPoint FROM userTable");

    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError().text();
        return;
    }

    QVector<Users *>account;
    while (query.next()) {
        Users *user = new Users;
        user->id = query.value("id").toInt();
        user->nickname = query.value("user_nickname").toString();
        user->win = query.value("winPoint").toInt();
        user->loss = query.value("lossPoint").toInt();
        account.push_back(user);
    }

}

void Leaderboards::setTitleShadow(){
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(12);                // how soft the shadow is
    shadow->setColor(QColor(0, 0, 0, 200));  // shadow color and transparency
    shadow->setOffset(7, 7);                 // offset (x, y)
    leaderboard_ui->title->setGraphicsEffect(shadow);
}
Leaderboards::~Leaderboards()
{
    delete leaderboard_ui;
}
