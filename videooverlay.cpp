#include "videooverlay.h"
#include <QMouseEvent>
#include <QDebug>
#include <QLineEdit>
#include <QStringList>
#include <QTextStream>
#include <QFile>
#include <cmath>

void VideoOverlay::mousePressEvent(QMouseEvent *e)
{

    QTableWidgetItem* x = new QTableWidgetItem;
    QTableWidgetItem* y = new QTableWidgetItem;
    QTableWidgetItem* time = new QTableWidgetItem;

    x->setTextAlignment(Qt::AlignCenter);
    y->setTextAlignment(Qt::AlignCenter);
    time->setTextAlignment(Qt::AlignCenter);

    QString xStr = QString::number(e->x()/mVideoPlayer->mRatio);
    QString yStr = QString::number((mVideoPlayer->height() - e->y())/mVideoPlayer->mRatio);
    QString position = QString::number(mVideoPlayer->getPlayer()->position()/100.0);

    int row = 0;

    if(mVideoPlayer->mHasChosenOutFile && mVideoPlayer->mHasChosenVid && !mVideoPlayer->mIsChoosingRatio){

        QTextStream outputStream(&mVideoPlayer->mOutputFile);
        outputStream <<  position << "," << xStr << "," << yStr << "\n";

        x->setText(xStr);
        y->setText(yStr);
        time->setText(position);

        mCoordinateTable->insertRow(row);
        mCoordinateTable->setItem(row,1,x);
        mCoordinateTable->setItem(row,2,y);
        mCoordinateTable->setItem(row,0,time);

        QString stringInt = mTextbox->text();
        int seekInt = stringInt.toInt();
        mVideoPlayer->seek(seekInt);
    }

    if(mVideoPlayer->mIsChoosingRatio && (mVideoPlayer->mHasChosenOutFile && mVideoPlayer->mHasChosenVid)){
        mPointsChosen++;

        if(mPointsChosen == 1){
            mFirstPointX = e->x();
            mFirstPointY = e->y();
        } else if(mPointsChosen == 2){
            int x = e->x();
            int y = e->y();
            double xDist = sqrt(mFirstPointX*mFirstPointX + x*x);
            double yDist = sqrt(mFirstPointY*mFirstPointY + y*y);
            mVideoPlayer->mRatio = sqrt(xDist*xDist + yDist*yDist);
            mVideoPlayer->mIsChoosingRatio = false;
        }
    }
}

void VideoOverlay::setVideoPlayer(VideoPlayer* vp){
    mVideoPlayer = vp;
}

void VideoOverlay::setTextbox(QLineEdit* le){
    mTextbox = le;
}

void VideoOverlay::setCoordinateTable(QTableWidget* ct){
    mCoordinateTable = ct;
}

VideoOverlay::VideoOverlay(QWidget *parent) :
    QWidget(parent)
{
    mPointsChosen = 0;
}
