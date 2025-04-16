#include "leaderboards.h"
#include "ui_leaderboards.h"
#include "dbmanager.h"
#include <QGraphicsDropShadowEffect>
#include <algorithm>
#include <QHBoxLayout>
#include <QFont>

Leaderboards::Leaderboards(QWidget *parent)
    : QWidget(parent)
    , leaderboard_ui(new Ui::leaderboards)
{
    leaderboard_ui->setupUi(this);
    setTitleShadow();
    QFont font("Klee");
    font.setPointSize(25);
    leaderboard_ui->leaderboard->setFont(font);
    leaderboard_ui->searchBar->setPlaceholderText("Enter a nickname");

    connect(leaderboard_ui->backBtn, &QPushButton::clicked, this, [=](){
        emit returnToLobby();
    });

    setUserLeaderboard();

    connect(leaderboard_ui->searchBar, &QLineEdit::textChanged, this, [=](QString str){
        leaderboard_ui->leaderboard->clear();
        for(auto &it : account){
            if(str.isEmpty() || it.nickname.contains(str, Qt::CaseInsensitive)){
                double winrate = (double)it.win / (it.win+it.loss) * 100;
                QString num = "#" + QString::number(it.id);
                  QString text = QString("%1  :  %2  |  Wins: %3  |  Losses: %4  |  WinRate: %5")
                   .arg(num)
                  .arg(it.nickname)
                      .arg(it.win)
                      .arg(it.loss)
                      .arg(winrate, 0, 'f', 2);
                  leaderboard_ui->leaderboard->addItem(text);
            }
        }
    });
}

void Leaderboards::setUserLeaderboard(){
    account.clear();
    QList userList = DbManager::instance().fetchUserInfo();
    for(auto &it : userList){
        Users user;
        user.id = it[0].toInt();
        user.nickname = it[2];
        user.win = it[3].toInt();
        user.loss = it[4].toInt();
        account.push_back(user);
    }

    std::sort(account.begin(), account.end(), [](Users& a, Users& b) {
        return a.win > b.win;
    });

    int count = 1;
    for(auto &it : account){
        it.id = count;
        count++;
    }

    leaderboard_ui->leaderboard->clear();
    for(auto &it : account){
        double winrate = (double)it.win / (it.win+it.loss) * 100;
        QString num = "#" + QString::number(it.id);
          QString text = QString("%1  :  %2  |  Wins: %3  |  Losses: %4  |  WinRate: %5")
           .arg(num)
          .arg(it.nickname)
              .arg(it.win)
              .arg(it.loss)
              .arg(winrate, 0, 'f', 2);
          leaderboard_ui->leaderboard->addItem(text);
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
