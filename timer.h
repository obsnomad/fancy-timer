#ifndef TIMER_H
#define TIMER_H

#include <QWidget>
#include <QTimer>
#include <QMediaPlayer>
#include <QMediaPlaylist>

namespace Ui {
class Timer;
}

class Timer : public QWidget
{
    Q_OBJECT

public:
    explicit Timer(QWidget *parent = 0);
    ~Timer();

public slots:
    void timeout();

protected:
    void keyPressEvent(QKeyEvent *);
    void setTimer();

private:
    Ui::Timer *ui;
    QTimer *timer = new QTimer;
    QMediaPlaylist *playlist = new QMediaPlaylist();
    QMediaPlayer *music = new QMediaPlayer;
    QMediaPlayer *alarm = new QMediaPlayer;
    QMediaPlayer *final = new QMediaPlayer;
    int counter;
    int alarmValue;
    QString alarmColor;
};

#endif // TIMER_H
