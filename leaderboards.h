#ifndef LEADERBOARDS_H
#define LEADERBOARDS_H

#include <QWidget>
#include "dbmanager.h"

namespace Ui {
class leaderboards;
}

class Leaderboards : public QWidget, protected DbManager
{
    Q_OBJECT

public:
    explicit Leaderboards(QWidget *parent = nullptr);
    void setTitleShadow();
    ~Leaderboards();
signals:
    void returnToLobby();
private:
    Ui::leaderboards *leaderboard_ui;
    class QListWidget *player_list;
};

#endif // LEADERBOARDS_H
