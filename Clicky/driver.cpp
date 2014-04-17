#include "driver.h"
#include "ui_driver.h"
#include <QMediaPlayer>

Driver::Driver(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Driver)
{
    ui->setupUi(this);
    QMediaPlayer *mediaPlayer = new QMediaPlayer;
    QVideoWidget *vid_widget = new QVideoWidget;

}

Driver::~Driver()
{
    delete ui;
}
