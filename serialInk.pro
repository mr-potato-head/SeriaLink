#-------------------------------------------------
#
# Project created by QtCreator 2016-05-27T21:16:40
#
#-------------------------------------------------

QT += core gui serialport

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
    src/pageselector.cc \
    src/session.cc \
    src/comportsettings.cc \
    src/localcomport.cc \
    src/comport.cc \
    src/addormodifyportdialog.cc \
    src/portinfowidget.cc \
    src/portpage.cc \
    src/sendwidget.cc \
    src/portview.cc \
    src/viewsettings.cc \
    src/viewsettingdialog.cc \
    src/dataformatter.cc \
    src/tableportview.cc \
    src/dumpportview.cc \
    src/aboutwindow.cc \
    src/comportmanager.cc \
    src/dumpmodepage.cc \
    src/manualmodepage.cc \
    src/menuwidget.cc \
    src/modepage.cc \
    src/terminalportview.cc \
    src/datapacket.cc \
    src/dataparser.cc

HEADERS += src/mainwindow.h \
    src/pageswitcher.h \
    src/topbar.h \
    src/centralwidget.h \
    src/pagecontainer.h \
    src/pageselector.h \
    src/session.h \
    src/comportsettings.h \
    src/comport.h \
    src/localcomport.h \
    src/addormodifyportdialog.h \
    src/portinfowidget.h \
    src/portpage.h \
    src/portview.h \
    src/sendwidget.h \
    src/viewsettings.h \
    src/viewsettingdialog.h \
    src/dataformatter.h \
    src/comportmanager.h \
    src/datapacket.h \
    src/modepage.h \
    src/manualmodepage.h \
    src/dumpmodepage.h \
    src/tableportview.h \
    src/dumpportview.h \
    src/terminalportview.h \
    src/dataparser.h \
    src/menuwidget.h \
    src/aboutwindow.h

OTHER_FILES += \
    LICENSE.txt \
    README.md

RESOURCES += \
    resources.qrc
