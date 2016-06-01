#-------------------------------------------------
#
# Project created by QtCreator 2016-05-27T21:16:40
#
#-------------------------------------------------

QT += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = serialInk
TEMPLATE = app

SOURCES += src/main.cc\
        src/mainwindow.cc \
    src/pageswitcher.cc \
    src/topbar.cc \
    src/centralwidget.cc \
    src/pagecontainer.cc \
    src/pageselector.cc

HEADERS += src/mainwindow.h \
    src/pageswitcher.h \
    src/topbar.h \
    src/centralwidget.h \
    src/pagecontainer.h \
    src/pageselector.h

OTHER_FILES += \
    LICENSE.txt \
    README.md
