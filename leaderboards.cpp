#include "leaderboards.h"
#include "ui_leaderboards.h"
#include <QSqlQueryModel>
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

    QSqlQueryModel query;
    query.setQuery("SELECT * FROM userTable");

    while (query.canFetchMore()){
        query.fetchMore();
    }

    for (int i = 0; i < query.rowCount(); i++)
    {
        // Your data
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
