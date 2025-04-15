#include "tictactoe.h"
#include "./ui_tictactoe.h"
#include <QFont>
#include <QMessageBox>
#include <QTimer>
#include <QColor>
#include <QFrame>

Tictactoe::Tictactoe(QWidget *parent)
    : QWidget(parent) , game_ui(new Ui::tictactoe_ui)
{
    game_ui->setupUi(this);

    setSpinner();
    startGame();

    connect(game_ui->backBtn, &QPushButton::clicked, this, [=](){
      QString warningMsg = QString("Do you really want to go back to Lobby?");

      QMessageBox::StandardButton reply = QMessageBox::question(this, "Game Over", warningMsg,
                                    QMessageBox::No | QMessageBox::Yes);
      if (reply == QMessageBox::Yes) {
        emit returnToLobby();
        startGame();
      }
    });

    for (auto &btn : btns) {
        connect(btn, &QPushButton::clicked, this, [&]() {
            if (!btn->text().isEmpty())
                return;

            // Set font and text
            QFont font = btn->font();
            font.setFamily("Klee");
            font.setBold(true);
            font.setPixelSize(btn->height()); // Scales with button
            btn->setFont(font);

            QString symbol;
            if(whichPlayer == 0){
                symbol= "X";
                game_ui->label_2->setText("Current Player: Player2");
                btn->setText(symbol);
                btn->setStyleSheet("QPushButton{"
                                   "border: none;"
                                   "color: red;"
                                   "}");
            }
            else{
                symbol = "O";
                game_ui->label_2->setText("Current Player: Player1");
                btn->setText(symbol);
                btn->setStyleSheet("QPushButton{"
                                   "border: none;"
                                   "color: blue;"
                                   "}");
            }

            whichPlayer = 1 - whichPlayer; // Toggle player

            // Parse position from accessibleName
            QString pos = btn->accessibleName();
            int row = pos[0].digitValue();
            int col = pos[1].digitValue();
            board[row][col] = symbol;

            max_turn++;
            QString winner = checkWinner(board).first;
            std::pair<QString, QString> coordinate = checkWinner(board).second;
            if(!winner.isEmpty()) {
                // FIX:
                // drawWinningLine(whichPlayer, coordinate);
                QString winnerMsg = QString("Player %1 wins! Play again?").arg(winner == "player1" ? 1 : 2);
                game_ui->label_2->setText("Current Player:");

                QMessageBox::StandardButton reply = QMessageBox::question(this, "Game Over", winnerMsg,
                                              QMessageBox::No | QMessageBox::Yes);
                if (reply == QMessageBox::Yes) {
                    spinner->start();
                    QTimer::singleShot(500, this, [this]() {
                        spinner->stop();
                    });
                    // FIX:
                    // winLine->hide();
                    startGame();
                } else {
                    emit returnToLobby();
                    startGame();
                }
            }
            //keeps checking if both players' turns end. When there's no winner, draw
            else if(max_turn == 9) {
                QString drawMsg = QString("Draw! Play again?");
                game_ui->label_2->setText("Current Player:");

                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(this, "Game Over", drawMsg,
                                              QMessageBox::No | QMessageBox::Yes);
                if (reply == QMessageBox::Yes) {
                    spinner->start();
                    QTimer::singleShot(500, this, [this]() {
                        spinner->stop();
                    });
                    startGame();
                } else {
                    emit returnToLobby();
                    startGame();
                }
            }
        });
    }
}

void Tictactoe::setSpinner(){
    spinner = new WaitingSpinnerWidget(this);

    spinner->setRoundness(70.0);
    spinner->setMinimumTrailOpacity(15.0);
    spinner->setTrailFadePercentage(70.0);
    spinner->setNumberOfLines(12);
    spinner->setLineLength(10);
    spinner->setLineWidth(5);
    spinner->setInnerRadius(10);
    spinner->setRevolutionsPerSecond(4);
}

void Tictactoe::startGame(){
    // FIX:
    // winLine = new QFrame(this);
    // winLine->hide();

    // Initialize board and buttons
    for (int i = 0; i < ROW_COL; ++i)
        for (int j = 0; j < ROW_COL; ++j)
            board[i][j] = "";

    QStringList positions = {
        "00", "01", "02",
        "10", "11", "12",
        "20", "21", "22"
    };

    btns = {game_ui->Btn00, game_ui->Btn01, game_ui->Btn02,
            game_ui->Btn10, game_ui->Btn11, game_ui->Btn12,
            game_ui->Btn20, game_ui->Btn21, game_ui->Btn22};

    // Reset all buttons
    for (auto &btn : btns) {
        btn->setText("");
        btn->setStyleSheet("");
        btn->setFont(QFont());
        btn->setFixedSize(245,173);
    }

    // Set accessible names
    for (int i = 0; i < btns.size(); ++i)
        btns[i]->setAccessibleName(positions[i]);

    whichPlayer = max_turn = 0;
    game_ui->label_2->setText("Current Player: Player1");
}


std::pair<QString, std::pair<QString, QString>> Tictactoe::checkWinner(QString board[ROW_COL][ROW_COL]){
    QString p1 = "player1", p2 = "player2";
    for(int i = 0; i < ROW_COL; i++){
        if(!board[i][0].isEmpty() && board[i][0] == board[i][1] && board[i][1] == board[i][2]){
            if(board[i][0] == "X"){
                QString coordinate_1, coordinate_2;
                coordinate_1 += QString::number(i); coordinate_1 +=QString::number(0);
                coordinate_2 += QString::number(i); coordinate_2 +=QString::number(2);
                return std::make_pair(p1, std::make_pair(coordinate_1, coordinate_2));
            }
            else{
                QString coordinate_1, coordinate_2;
                coordinate_1 += QString::number(i); coordinate_1 +=QString::number(0);
                coordinate_2 += QString::number(i); coordinate_2 +=QString::number(2);
                return std::make_pair(p2, std::make_pair(coordinate_1, coordinate_2));
            }
        }
        if (!board[0][i].isEmpty() && board[0][i] == board[1][i] && board[1][i] == board[2][i]){
            if(board[0][i] == "X"){
                QString coordinate_1, coordinate_2;
                coordinate_1 += QString::number(0); coordinate_1 +=QString::number(i);
                coordinate_2 += QString::number(2); coordinate_2 +=QString::number(i);
                return std::make_pair(p1, std::make_pair(coordinate_1, coordinate_2));
            }
            else{
                QString coordinate_1, coordinate_2;
                coordinate_1 += QString::number(0); coordinate_1 +=QString::number(i);
                coordinate_2 += QString::number(2); coordinate_2 +=QString::number(i);
                return std::make_pair(p2, std::make_pair(coordinate_1, coordinate_2));
            }

        }
    }

    // Diagonal (top-left to bottom-right)
    if (!board[0][0].isEmpty() && board[0][0] == board[1][1] && board[1][1] == board[2][2]){
        if(board[0][0] == "X"){
                QString coordinate = "diagonal";
                return std::make_pair(p1,std::make_pair(coordinate,""));
        }
        else{
                QString coordinate = "diagonal";
                return std::make_pair(p2,std::make_pair(coordinate,""));
        }
    }

    // Diagonal (top-right to bottom-left)
    if (!board[0][2].isEmpty() && board[0][2] == board[1][1] && board[1][1] == board[2][0]){
        if(board[0][2] == "X"){
                QString coordinate = "rdiagonal";
                return std::make_pair(p1,std::make_pair(coordinate, ""));
        }
        else{
                QString coordinate = "rdiagonal";
                return std::make_pair(p1,std::make_pair(coordinate,""));
        }
    }
    return std::make_pair("",std::make_pair("",""));
}

Tictactoe::~Tictactoe()
{
    delete game_ui;
}

// FIX:
// void tictactoe::drawWinningLine(bool whichPlayer, std::pair<QString, QString> coordinate) {
// if(whichPlayer == 1){
// winLine->setStyleSheet("background-color: red;");
// }
// else{
// winLine->setStyleSheet("background-color: blue;");
// }
// QPushButton* btn0, *btn1, *btn2;
// QPoint x, y;

// if(coordinate.first == "00" && coordinate.second == "02"){
// btn0 = ui->Btn00;
// btn1 = ui->Btn01;
// btn2 = ui->Btn02;

// if (!btn0 || !btn1 || !btn2 || !winLine) return;
// }
// else if(coordinate.first == "10" && coordinate.second == "12"){
// btn0 = ui->Btn10;
// btn1 = ui->Btn11;
// btn2 = ui->Btn12;

// if (!btn0 || !btn1 || !btn2 || !winLine) return;
// }
// else if(coordinate.first == "20" && coordinate.second == "22"){
// btn0 = ui->Btn20;
// btn1 = ui->Btn21;
// btn2 = ui->Btn22;

// if (!btn0 || !btn1 || !btn2 || !winLine) return;
// }
// else if(coordinate.first == "00" && coordinate.second == "20"){
// btn0 = ui->Btn00;
// btn1 = ui->Btn10;
// btn2 = ui->Btn20;

// if (!btn0 || !btn1 || !btn2 || !winLine) return;
// }
// else if(coordinate.first == "01" && coordinate.second == "21"){
// btn0 = ui->Btn01;
// btn1 = ui->Btn11;
// btn2 = ui->Btn21;

// if (!btn0 || !btn1 || !btn2 || !winLine) return;
// }
// else if(coordinate.first == "02" && coordinate.second == "22"){
// btn0 = ui->Btn02;
// btn1 = ui->Btn12;
// btn2 = ui->Btn22;

// if (!btn0 || !btn1 || !btn2 || !winLine) return;
// }
// else if(coordinate.first == "diagonal"){
// btn0 = ui->Btn00;
// btn1 = ui->Btn11;
// btn2 = ui->Btn22;

// if (!btn0 || !btn1 || !btn2 || !winLine) return;
// }
// else if(coordinate.first == "rdiagonal"){
// btn0 = ui->Btn02;
// btn1 = ui->Btn11;
// btn2 = ui->Btn20;

// if (!btn0 || !btn1 || !btn2 || !winLine) return;
// }
// x = btn0->mapTo(this, QPoint(0, btn0->height() / 2));
// y = btn2->mapTo(this, QPoint(0, btn2->height() / 2));
// int lineLength = btn0->width() * 3+32;
// int lineThickness = 5;
// qDebug() << x.x() << " " << y.y() << "\n";

// winLine->setGeometry(x.x(), y.y(), lineLength, lineThickness);
// winLine->show();
// }
