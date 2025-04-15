#ifndef LOBBY_H
#define LOBBY_H

#include <QWidget>

namespace Ui {
class lobby;
}

class Lobby : public QWidget
{
    Q_OBJECT

public:
    explicit Lobby(QWidget *parent = nullptr);
    class QPushButton *getButton();
    void setTitleShadow();
    ~Lobby();
signals:
    void goToLogin();
    void playGame();
    void goToLeaderboards();
    void goToSetting();
private:
    Ui::lobby *lobby_ui;
};

#endif // LOBBY_H
