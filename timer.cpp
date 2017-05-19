#include "timer.h"
#include "ui_timer.h"
#include <QWindow>
#include <QDesktopWidget>
#include <QScreen>
#include <QSettings>
#include <QUrl>
#include <QFileInfo>
#include <QKeyEvent>
#include <QFont>
#include <QTime>

Timer::Timer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Timer)
{
    ui->setupUi(this);

    // Load settings
    QSettings settings("config.ini", QSettings::IniFormat);

    // Set size and show window
    QRect ScreenSize = QApplication::desktop()->screenGeometry(QApplication::desktop()->screenCount() - 1);
    this->showFullScreen();
    ui->mainLabel->setGeometry(0, 0, ScreenSize.width(), ScreenSize.height());
    ui->mainLabel->setText("");
    ui->timerLabel->setGeometry(0, 0, ScreenSize.width(), ScreenSize.height());

    // Set background color
    QString backgroundColor = settings.value("BACKGROUND_COLOR", "#fff").toString();
    QString fontColor = settings.value("FONT_COLOR", "#000").toString();
    this->setStyleSheet("background-color: " + backgroundColor + "; color: " + fontColor);

    // Set background image
    QString backgroundUrl = settings.value("BACKGROUND_IMAGE", "").toString();
    if(backgroundUrl.length() > 0) {
        QPixmap BGImage(backgroundUrl);
        BGImage = BGImage.scaled(ui->mainLabel->width(), ui->mainLabel->height(), Qt::KeepAspectRatio);
        ui->mainLabel->setAlignment(Qt::AlignCenter);
        ui->mainLabel->setPixmap(BGImage);
    }

    // Set audio background
    QString musicUrl = settings.value("MUSIC", "").toString();
    if(musicUrl.length() > 0) {
        playlist->addMedia(QUrl::fromLocalFile(QFileInfo(musicUrl).absoluteFilePath()));
        playlist->setPlaybackMode(QMediaPlaylist::Loop);
        music->setPlaylist(playlist);
        music->setVolume(100);
        music->play();
    }

    // Set alarm sound
    QString alarmUrl = settings.value("ALARM", "").toString();
    if(alarmUrl.length() > 0) {
        alarm->setMedia(QUrl::fromLocalFile(QFileInfo(alarmUrl).absoluteFilePath()));
        alarm->setVolume(100);
    }

    // Set final sound
    QString finalUrl = settings.value("FINAL", "").toString();
    if(finalUrl.length() > 0) {
        final->setMedia(QUrl::fromLocalFile(QFileInfo(finalUrl).absoluteFilePath()));
        final->setVolume(100);
    }

    // Timer label styles
    QString timerFontFamily = settings.value("TIMER_FONT_FAMILY", QVariant(QFont::SansSerif).toString()).toString();
    int timerFontSize = settings.value("TIMER_FONT_SIZE", 150).toInt();
    bool timerFontIsBold = settings.value("TIMER_FONT_BOLD", 0).toBool();
    QString timerFontColor = settings.value("TIMER_FONT_COLOR", fontColor).toString();
    alarmColor = settings.value("TIMER_FONT_COLOR_ALARM", timerFontColor).toString();
    QFont font(timerFontFamily, timerFontSize, timerFontIsBold ? QFont::Bold : QFont::Normal);
    ui->timerLabel->setFont(font);
    ui->timerLabel->setStyleSheet("color: " + timerFontColor);
    ui->timerLabel->setAttribute(Qt::WA_TranslucentBackground);
    ui->timerLabel->setAlignment(Qt::AlignCenter);

    // Run timer
    QStringList arguments = QCoreApplication::arguments();
    if(arguments.length() > 1) {
        counter = arguments.at(1).toInt();
        if(arguments.length() > 2) {
            alarmValue = arguments.at(2).toInt();
        }
    }
    if(!counter) {
        counter = settings.value("TIMER_DEFAULT_VALUE", 60).toInt();
    }
    if(!alarmValue) {
        alarmValue = settings.value("TIMER_ALARM_VALUE", -1).toInt();
    }
    setTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
    timer->start(1000);
}

void Timer::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        QApplication::quit();
    }
}

void Timer::timeout()
{
    counter--;
    setTimer();
}

void Timer::setTimer()
{
    QTime time(0, (int)counter / 60, counter % 60);
    ui->timerLabel->setText(time.toString("m:ss"));
    if(counter == 0) {
        music->stop();
        timer->stop();
        final->play();
    }
    else if(counter <= alarmValue) {
        ui->timerLabel->setStyleSheet("color: " + alarmColor);
        alarm->play();
    }
}

Timer::~Timer()
{
    delete ui;
}
