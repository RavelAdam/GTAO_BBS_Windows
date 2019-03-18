#-------------------------------------------------
#
# Project created by QtCreator 2019-03-18T16:15:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GTAO_BBS_Windows
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    Custom_Classes/enhancedtimer.cpp \
    Main/main.cpp \
    Main/mainwindow.cpp \
    Widgets/BunkerWidget/bunkerwidget.cpp \
    Widgets/GlobalTabWidget/globaltabwidget.cpp \
    Widgets/MCWidget/mcwidget.cpp \
    Widgets/NightclubWidget/nightclubwidget.cpp

HEADERS += \
    Custom_Classes/enhancedtimer.h \
    Main/mainwindow.h \
    Widgets/BunkerWidget/bunkerwidget.h \
    Widgets/GlobalTabWidget/globaltabwidget.h \
    Widgets/MCWidget/mcwidget.h \
    Widgets/NightclubWidget/nightclubwidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
