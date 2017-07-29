#-------------------------------------------------
#
# Project created by QtCreator 2014-12-22T14:53:33
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = subSpy
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    	qcustomplot.cpp

HEADERS  += mainwindow.hpp \
    		qcustomplot.h


FORMS    += mainwindow.ui

#RC_FILE = subspy.rc
win32:RC_ICONS += Spy_icon.ico
win32:RC_FILE += subspy.rc

RESOURCES += \
    appresources.qrc


