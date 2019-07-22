#-------------------------------------------------
#
# Project created by QtCreator 2016-02-29T09:00:50
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ATcenter
TEMPLATE = app
RC_FILE =  atcenter.rc

SOURCES += main.cpp\
        mainwindow.cpp \
    delay.cpp

HEADERS  += mainwindow.h \
    delay.h

FORMS    += mainwindow.ui
