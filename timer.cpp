#include "timer.h"
#include "ui_timer.h"
#include <QWindow>
#include <QDesktopWidget>
#include <QScreen>
#include <QSettings>

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

    // Set background
    QString backgroundUrl = settings.value("BACKGROUND", "").toString();
    if(backgroundUrl.length() > 0) {
        QPixmap BGImage(backgroundUrl);
        BGImage = BGImage.scaled(ui->mainLabel->width(), ui->mainLabel->height(), Qt::KeepAspectRatio);
        ui->mainLabel->setAlignment(Qt::AlignCenter);
        ui->mainLabel->setPixmap(BGImage);
    }
}

Timer::~Timer()
{
    delete ui;
}
