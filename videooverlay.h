#ifndef VIDEOOVERLAY_H
#define VIDEOOVERLAY_H
#include "../videoplayer.h"

#include <QWidget>
#include <QLineEdit>

class VideoOverlay : public QWidget
{
    Q_OBJECT

protected:
    void    mousePressEvent(QMouseEvent *event);

public:
    VideoPlayer* mVideoPlayer;
    QLineEdit* mTextbox;
    QTableWidget* mCoordinateTable;
    int mPointsChosen;
    //Keeps track of the points for ratio setting
    int mFirstPointX;
    int mFirstPointY;

    explicit VideoOverlay(QWidget *parent = 0);
    void setVideoPlayer(VideoPlayer* vp);
    void setTextbox(QLineEdit* le);
    void setCoordinateTable(QTableWidget* ct);

signals:

public slots:

};

#endif // VIDEOOVERLAY_H
