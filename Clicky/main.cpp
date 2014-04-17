#include "../videoplayer.h"
#include "../videooverlay.h"
#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow mw;

    VideoPlayer* vp = new VideoPlayer;
    VideoOverlay* vo = new VideoOverlay;
    vo->setVideoPlayer(vp);


    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(vp->getVideoPlayer());
    vo->setTextbox(vp->getTexbox());
    vo->setCoordinateTable(vp->getCoordinateTable());

    vo->setLayout(layout);
    mw.setStyleSheet("background-color: grey; border-radius:2px");
    mw.setCentralWidget(vo);
    mw.setMenuBar(vp->createMenuBar());
    mw.resize(QSize(1280, 500));
    mw.show();

    return app.exec();
}
