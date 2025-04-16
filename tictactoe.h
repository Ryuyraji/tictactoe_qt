#ifndef TICTACTOE_H
#define TICTACTOE_H

#include "waitingspinnerwidget.h"
#include <QWidget>
#define ROW_COL 3

QT_BEGIN_NAMESPACE
namespace Ui {
class tictactoe_ui;
}
QT_END_NAMESPACE

class Tictactoe : public QWidget
{
    Q_OBJECT
public:
    Tictactoe(QWidget *parent = nullptr);
    ~Tictactoe();
    std::pair<QString,std::pair<QString, QString>> checkWinner(QString[ROW_COL][ROW_COL]);
    void startGame();
    void setSpinner();
    void resetUser();
    void soundEffect();
    void victorySound();
    void losingSound();

signals:
    void returnToLobby();
    void winGame(QString);
    void loseGame(QString);

private:
    Ui::tictactoe_ui *game_ui;
    WaitingSpinnerWidget* spinner;
    QVector<class QPushButton *>btns;
    QFont font;
    QString board[3][3];
    bool whichPlayer;
    int max_turn;
    QString currentUser;
    QString currentUserId;
    class QMediaPlayer *m_player;
    class QAudioOutput *m_audioOutput;
    QPair<int, int> moveable;
};
#endif // TICTACTOE_H
