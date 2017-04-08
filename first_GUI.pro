#-------------------------------------------------
#
# Project created by QtCreator 2017-03-24T20:29:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = first_GUI
TEMPLATE = app


SOURCES += main.cpp\
    frontpanel.cpp \
    canhandler.cpp

HEADERS  += \
    frontpanel.h \
    canhandler.h

FORMS    += \
    frontpanel.ui

unix:!macx: LIBS += -L$$PWD/../kvaser/linuxcan/canlib/ -lcanlib

INCLUDEPATH += $$PWD/../kvaser/linuxcan/canlib
DEPENDPATH += $$PWD/../kvaser/linuxcan/canlib

