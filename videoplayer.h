#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QWidget>
#include <QPushButton>
#include <QMenuBar>
#include <QMediaPlayer>
#include <QPoint>
#include <QMouseEvent>
#include <QLineEdit>
#include <QTableWidget>
#include <QFile>
#include <QTextStream>
#include <QLabel>

class VideoPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit VideoPlayer(QWidget *parent = 0);
    QPushButton* getButtonWithText(QString text);
    QWidget* getButtonsWidget();
    QMenuBar* createMenuBar();
    QWidget* getVideoPlayer();

    QWidget* createFormattedTexbox();
    QLabel* createFormattedLabel(const QString str);
    QLineEdit* getTexbox();
    QTableWidget* getNewCoordinateTable();
    QTableWidget* getCoordinateTable();
    QMediaPlayer* getPlayer();
    QVideoWidget* setVideoPlayer();
    void resetVideoPlayer();



public slots:
    void played();
    void seek(int intToSeekBy);
    void saveFile();
    void setVideoFile();
    void setRatio();
    void quit();
    void reset();

private:
    QMediaPlayer* mplayer;


public:
    QLineEdit* mTextbox;
    QTableWidget* mCoordinatesTable;
    QFile mOutputFile;
    double mRatio;
    bool mHasChosenVid;
    bool mHasChosenOutFile;
    bool mIsChoosingRatio;
};

#endif // VIDEOPLAYER_H
