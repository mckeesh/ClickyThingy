#include "videoplayer.h"
#include <qmediaplayer.h>
#include <QVideoWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QMenuBar>
#include <QMenu>
#include <QLineEdit>
#include <QFileDialog>
#include <unistd.h>
#include <QScrollBar>
#include <QTextEdit>
#include <QMessageBox>
#include <QLabel>



QPushButton* VideoPlayer::getButtonWithText(QString text){
    QPushButton* button = new QPushButton(text);
    button->setFixedWidth(100);
    button->setFixedHeight(20);
    button->setStyleSheet("background-color: #FFC038; border-radius:2px; border: 2px solid black;");
    return button;
}

QLabel* VideoPlayer::createFormattedLabel(const QString str){
    QLabel* label = new QLabel;
    label->setText(str);
    label->setAlignment(Qt::AlignTop);
    label->setFixedSize(QSize(100,20));
    label->setStyleSheet("background-color: #FFC038; border-radius: 2px; border: 2px solid black;");
    label->setContentsMargins(0,0,0,0);
    label->setAlignment(Qt::AlignCenter);
    return label;
}

QWidget* VideoPlayer::createFormattedTexbox(){
    QWidget* bigWidget = new QWidget;
    QLineEdit* textbox = new QLineEdit;
    QLabel* description = createFormattedLabel("Seek Amount");
    QHBoxLayout* layout = new QHBoxLayout;

    layout->addWidget(textbox);
    layout->addWidget(description);
    layout->setContentsMargins(0,0,0,0);

    textbox->setValidator(new QIntValidator(0, 100000, this));
    textbox->setFixedSize(QSize(70,20));
    textbox->setText("75");
    textbox->setStyleSheet("background-color: #FFC038;");
    textbox->setAlignment(Qt::AlignTop);

    mTextbox = textbox;
    bigWidget->setLayout(layout);
    bigWidget->setStyleSheet("background-color: #FFC038;");
    bigWidget->setFixedSize(QSize(200,20));
    return bigWidget;
}

QTableWidget* VideoPlayer::getNewCoordinateTable(){
      QTableWidget* tableWidget = new QTableWidget(10, 3, this);
      QScrollBar* scrollBar = new QScrollBar;
      QStringList headers;

      headers << "Time" << "X" << "Y";
      tableWidget->setHorizontalHeaderLabels(headers);
      tableWidget->setMaximumSize(QSize(398,200));
      tableWidget->setAlternatingRowColors(true);
      tableWidget->setStyleSheet("QTableWidget{ alternate-background-color: #64D8F3;background-color: #3AD0F3; margin: 0 auto;}"
                                 "QHeaderView::section { background-color:#3A7C8B };");
      tableWidget->setVerticalScrollBar(scrollBar);
      scrollBar->setStyleSheet("width: 0px; background-color: #3AD0F3;");

      return tableWidget;
}

QLineEdit* VideoPlayer::getTexbox(){
    return mTextbox;
}

void VideoPlayer::played(){
    mplayer->play();
}

void VideoPlayer::reset(){
    exit(0);
}

void VideoPlayer::quit(){
    exit(0);
}

void VideoPlayer::saveFile(){
    const QString str = QFileDialog::getSaveFileName(this, tr("Choose an output file!"), "ClickyThingyOut", tr("Comma-Separated Value Files (*.csv)"));
    mOutputFile.setFileName(str);
    if(!mOutputFile.open(QIODevice::ReadWrite)){
        qDebug() << "We failed to open that file for some reason :/";
    }
    mHasChosenOutFile = true;
    if(mHasChosenVid){
        mplayer->play();
        mplayer->pause();
    }
}

void VideoPlayer::setVideoFile(){
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Video"), "~", tr("Video Files (*.mp4 *.mov)"));

    mplayer->setMedia(QUrl::fromLocalFile(fileName));
    mHasChosenVid = true;

    if(mHasChosenOutFile){
        mplayer->play();
        mplayer->pause();
    }
}

void VideoPlayer::setRatio(){
    if(mHasChosenOutFile && mHasChosenVid){
        mIsChoosingRatio = true;
    } else if (!mHasChosenOutFile){
        QMessageBox messageBox(this);
        messageBox.setText("Please choose an output file.\nThis way, if the application crashes, you still have all your data.");
        messageBox.exec();
    } else if (!mHasChosenVid){
        QMessageBox messageBox(this);
        messageBox.setText("Please choose a video file.");
        messageBox.exec();
    }
}

//TODO Get this working better
void VideoPlayer::seek(int intToSeekBy){
    if(mplayer->position() != mplayer->duration()){
        mplayer->play();
        usleep(intToSeekBy*1000);
        mplayer->pause();
//        int pos = mplayer->position();
//        qDebug() << pos;
//        qDebug() << intToSeekBy;
//        mplayer->setPosition(pos + intToSeekBy);
//        usleep(1000);
//        qDebug() << mplayer->position();
    } else {

        QMessageBox messageBox(this);
        messageBox.setText("Select next video and output file!\nYour results are safely stored in your output file. Make sure to name your output file something different this time though :)");
        messageBox.exec();

        mHasChosenOutFile = false;
        mHasChosenVid = false;
        mRatio = 1;
    }
}

QWidget* VideoPlayer::getButtonsWidget(){

    QHBoxLayout *layout = new QHBoxLayout;
    QWidget *widget = new QWidget;

    widget->setLayout(layout);
    widget->setMaximumSize(QSize(1280,25));

    QPushButton* button = getButtonWithText("Set Output File");
    QPushButton* button2 = getButtonWithText("Set Video File");
    QPushButton* button3 = getButtonWithText("Set Unit Ratio");
    QPushButton* button4 = getButtonWithText("Reset");
    QPushButton* button5 = getButtonWithText("Quit");

    layout->addWidget(button);
    layout->addWidget(button2);
    layout->addWidget(button3);
    layout->addWidget(button4);
    layout->addWidget(button5);
    layout->addWidget(createFormattedTexbox());
    layout->setContentsMargins(0,0,0,0);

    QObject::connect(button, SIGNAL(clicked()),this, SLOT(saveFile()));
    QObject::connect(button2, SIGNAL(clicked()),this, SLOT(setVideoFile()));
    QObject::connect(button3, SIGNAL(clicked()),this, SLOT(setRatio()));
    QObject::connect(button4, SIGNAL(clicked()),this, SLOT(reset()));
    QObject::connect(button5, SIGNAL(clicked()),this, SLOT(quit()));

    return widget;
}

 QMenuBar* VideoPlayer::createMenuBar(){
      QMenuBar *menuBar = new  QMenuBar;
      QMenu *fileMenu = new QMenu("File");
      QAction *exitAction = new QAction("Exit",fileMenu);
      fileMenu->addAction(exitAction);
      menuBar->addMenu(fileMenu);

      return menuBar;
 }

 QMediaPlayer* VideoPlayer::getPlayer(){
     return mplayer;
 }

 QTableWidget* VideoPlayer::getCoordinateTable(){
     return mCoordinatesTable;
 }

 void VideoPlayer::resetVideoPlayer(){
     QVideoWidget* vid_widget = new QVideoWidget();
     vid_widget->setAspectRatioMode(Qt::IgnoreAspectRatio);
     vid_widget->setMinimumSize(QSize(1280, 600));
     vid_widget->setMaximumSize(QSize(10000,5000));
     vid_widget->setContentsMargins(0,0,0,0);
     mplayer->setVideoOutput(vid_widget);
     mplayer->setPlaybackRate(1);
     mplayer->play();
     mplayer->pause();
 }

 QVideoWidget* VideoPlayer::setVideoPlayer(){
     QVideoWidget* vid_widget = new QVideoWidget();
     vid_widget->setAspectRatioMode(Qt::IgnoreAspectRatio);
     vid_widget->setMinimumSize(QSize(1280, 600));
     vid_widget->setMaximumSize(QSize(10000,5000));
     vid_widget->setContentsMargins(0,0,0,0);

     mplayer->setVideoOutput(vid_widget);
     mplayer->setPlaybackRate(1);

     return vid_widget;
 }

 QWidget* VideoPlayer::getVideoPlayer(){

     QVBoxLayout *layout = new QVBoxLayout;
     QWidget *widget = new QWidget;

     layout->addWidget(setVideoPlayer());
     layout->addWidget(getButtonsWidget());
     layout->addWidget(mCoordinatesTable);

     mplayer->play();
     widget->setLayout(layout);
     widget->resize(QSize(1280, 500));
     mplayer->pause();

     return widget;
 }

VideoPlayer::VideoPlayer(QWidget *parent) :
    QWidget(parent)
{
    mRatio = 1;
    mHasChosenOutFile = false;
    mHasChosenVid = false;
    mIsChoosingRatio = false;
    mplayer = new QMediaPlayer;
    mCoordinatesTable = getNewCoordinateTable();
}
