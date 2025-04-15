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
    void drawWinningLine(bool, std::pair<QString, QString>);

signals:
    void returnToLobby();

private:
    Ui::tictactoe_ui *game_ui;
    WaitingSpinnerWidget* spinner;
    QVector<class QPushButton *>btns;
    QFont font;
    QString board[3][3];
    bool whichPlayer;
    int max_turn;
    // class QFrame *winLine;
};
#endif // TICTACTOE_H
