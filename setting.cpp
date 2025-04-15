#include "setting.h"
#include "./ui_setting.h"
#include <QMediaPlayer>
#include <QAudioOutput>

Setting::Setting(QWidget *parent) : QWidget(parent), setting_ui(new Ui::Form) {
    setting_ui->setupUi(this);

    bgm_init();

    connect(setting_ui->backBtn, &QPushButton::clicked, this, [=](){
        emit returnToLobby();
    });

    connect(setting_ui->musicState, &QPushButton::clicked, this, [=](){
        if(!music_on){
            this->playMusic();
            setting_ui->musicState->setText("Music Off");
            music_on = true;
        }
        else{
            this->stopMusic();
            setting_ui->musicState->setText("Music On");
            music_on = false;
        }
    });

    connect(setting_ui->volumeSlider, &QSlider::valueChanged, this, [&](int vol){
            this->sliderValueChange(vol);
    });
}

void Setting::bgm_init(){
    music_on = true;
    m_player = new QMediaPlayer;
    m_audioOutput = new QAudioOutput;
    m_player->setAudioOutput(m_audioOutput);

    setting_ui->volumeSlider->setValue(setting_ui->volumeSlider->maximum());
    float volValue = setting_ui->volumeSlider->value() / 100.0;
    m_audioOutput->setVolume(volValue);

    m_player->setSource(QUrl("qrc:/bgm/bgm.mp3"));
    m_player->setLoops(QMediaPlayer::Infinite);
    m_player->play();
}

void Setting::playMusic(){
    m_player->setSource(QUrl("qrc:/bgm/bgm.mp3"));
    m_player->play();
}

void Setting::stopMusic(){
    int state = m_player->playbackState();

    if (state == QMediaPlayer::PlayingState) {
        m_player->stop();
    }
}

void Setting::sliderValueChange(int val){
    setting_ui->volume->setText(QString("%1 %").arg(val));
    float volValue = val / 100.0;
    m_audioOutput->setVolume(volValue);
}

Setting::~Setting(){}
