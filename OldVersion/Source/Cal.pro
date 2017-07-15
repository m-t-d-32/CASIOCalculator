#-------------------------------------------------
#
# Project created by QtCreator 2017-06-26T07:39:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Cal
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    active.cpp \
    calculate.cpp \
    dialog.cpp \
    fraction.cpp \
    start.cpp

HEADERS  += mainwindow.h \
    active.h \
    calculate.h \
    dialog.h \
    fraction.h \
    const.h \
    start.h

FORMS    += mainwindow.ui \
    dialog.ui \
    start.ui

DISTFILES +=
RC_FILE += CCC.rc
CONFIG +=C++11
RESOURCES += \
    ccc.qrc
