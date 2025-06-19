#-------------------------------------------------
#
# Project created by QtCreator 2016-12-02T09:23:13
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += charts
QT       += serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
win32:RC_ICONS += ppg_icon.ico
TARGET = MAX86916_sPO2
TEMPLATE = app
VERSION = 0.0.0.1
DEFINES += APP_VERSION=\\\"$$VERSION\\\"
SOURCES += main.cpp\
        mainwindow.cpp \
    chart.cpp
HEADERS  += mainwindow.h \
         chart.h
FORMS    += mainwindow.ui
