#ifndef LEADERBOARDS_H
#define LEADERBOARDS_H

#include <QWidget>

namespace Ui {
class leaderboards;
}

typedef struct {
    int id;
    QString nickname;
    int win;
    int loss;
} Users;

class Leaderboards : public QWidget
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
