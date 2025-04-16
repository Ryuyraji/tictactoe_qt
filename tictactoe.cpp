#include "tictactoe.h"
#include "./ui_tictactoe.h"
#include "Login.h"
#include "dbmanager.h"
#include <QFont>
#include <QMessageBox>
#include <QTimer>
#include <QColor>
#include <QFrame>
#include <QMediaPlayer>
#include <QAudioOutput>

Tictactoe::Tictactoe(QWidget *parent)
    : QWidget(parent) , game_ui(new Ui::tictactoe_ui)
{
    game_ui->setupUi(this);

    currentUser = "";

    setSpinner();
    startGame();

    connect(&Login::instance(), &Login::loginSucceed, this, [&](QString userInfo){
        currentUserId = userInfo;
        currentUser = DbManager::instance().retrieveUserNickname(userInfo);
        game_ui->label_2->setText("Current Player: " + currentUser);
    });

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
            font.setPixelSize(200);
            btn->setFont(font);

            QString symbol;
            if(whichPlayer == 0){
                symbol= "X";
                game_ui->label_2->setText("Current Player: Computer");
                btn->setText(symbol);
                btn->setStyleSheet("QPushButton{"
                                   "border: red;"
                                   "color: red;"
                                   "}");
                soundEffect();
            }
            else{
                symbol = "O";
                game_ui->label_2->setText("Current Player: "+ currentUser);
                btn->setText(symbol);
                btn->setStyleSheet("QPushButton{"
                                   "border: blue;"
                                   "color: blue;"
                                   "}");
                soundEffect();
            }

            whichPlayer = 1 - whichPlayer;

            // Parse position from accessibleName
            QString pos = btn->accessibleName();
            int row = pos[0].digitValue();
            int col = pos[1].digitValue();
            board[row][col] = symbol;

            max_turn++;
            QString winner = checkWinner(board).first;
            std::pair<QString, QString> coordinate = checkWinner(board).second;
            if(!winner.isEmpty()) {
                QString winnerMsg = QString("%1 wins! Play again?").arg(winner == "player1" ? currentUser : "Computer");
                if(winner == "player1"){
                    victorySound();
                    DbManager::instance().addWinPoint(currentUserId);
                    emit winGame(currentUserId);
                    game_ui->label_2->setText("Current Player:");

                    QMessageBox::StandardButton reply = QMessageBox::question(this, "Game Over", winnerMsg,
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
                else{
                    game_ui->label_2->setText("Current Player:");
                    DbManager::instance().addLossPoint(currentUserId);
                    emit loseGame(currentUserId);

                    QMessageBox::StandardButton reply = QMessageBox::question(this, "Game Over", "You lost! " + winnerMsg,
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
            }
            //keeps checking if both players' turns end. When there's no winner, draw
            else if(max_turn == 9) {
                losingSound();
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

    game_ui->gridLayout->setSpacing(3);
    game_ui->gridLayout->setContentsMargins(1, 1, 1, 1);

    // Reset all buttons
    for (auto &btn : btns) {
        btn->setText("");
        btn->setStyleSheet( "QPushButton{"
                            "color: white;"
                            "background-color: rgba(0, 0, 0, 148);"
                            "border: none;}"
                            "QPushButton:hover{"
                            "background-color: rgb(190, 190, 190);}"
                            "QPushButton:pressed{"
                            "background-color: rgb(170, 170, 170);}");
        btn->setMaximumSize(250, 250);
    }

    // Set accessible names
    for (int i = 0; i < btns.size(); ++i)
        btns[i]->setAccessibleName(positions[i]);

    whichPlayer = max_turn = 0;
    game_ui->label_2->setText("Current Player: " + currentUser);
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

void Tictactoe::soundEffect() {
    m_player = new QMediaPlayer;
    m_audioOutput = new QAudioOutput;
    m_player->setAudioOutput(m_audioOutput);

    m_player->setSource(QUrl("qrc:/bgm/pop.mp3"));
    m_player->play();
}

void Tictactoe::victorySound() {
    m_player = new QMediaPlayer;
    m_audioOutput = new QAudioOutput;
    m_player->setAudioOutput(m_audioOutput);

    m_player->setSource(QUrl(":/bgm/victory.mp3"));
    m_player->play();
}

void Tictactoe::losingSound() {
    m_player = new QMediaPlayer;
    m_audioOutput = new QAudioOutput;
    m_player->setAudioOutput(m_audioOutput);

    m_player->setSource(QUrl("qrc:/bgm/losing.mp3"));
    m_player->play();
}

void Tictactoe::resetUser() {
    currentUser = "";
    game_ui->label_2->setText("Current Player:");
}

Tictactoe::~Tictactoe()
{
    delete game_ui;
}
