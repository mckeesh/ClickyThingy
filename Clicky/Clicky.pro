#-------------------------------------------------
#
# Project created by QtCreator 2014-02-27T19:43:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Clicky
TEMPLATE = app

QT += multimedia gui multimediawidgets

SOURCES += main.cpp \
    ../videoplayer.cpp \
    ../videooverlay.cpp

HEADERS += \
    ../videoplayer.h \
    ../videooverlay.h

DESTDIR = .
ICON = mouse.icns
