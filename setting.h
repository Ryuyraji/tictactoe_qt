#ifndef SETTING_H
#define SETTING_H
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Form;
}
QT_END_NAMESPACE

class Setting : public QWidget
{
    Q_OBJECT
public:
    Setting(QWidget *parent = nullptr);
    void bgm_init();
    ~Setting();
signals:
    void returnToLobby();
public slots:
    void playMusic();
    void stopMusic();
    void sliderValueChange(int val);

private:
    Ui::Form           *setting_ui;
    class QMediaPlayer *m_player;
    class QAudioOutput *m_audioOutput;
    bool                music_on;
};

#endif // SETTING_H
