#-------------------------------------------------
#
# Project created by QtCreator 2017-08-09T10:19:11
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CASIO7
TEMPLATE = app


SOURCES += main.cpp\
        controller.cpp \
    calculate.cpp \
    fraction.cpp \
    baseconv.cpp

HEADERS  += controller.h \
    calculate.h \
    fraction.h \
    const.h \
    baseconv.h

FORMS    += controller.ui

RESOURCES += \
    backgrounds.qrc

RC_ICONS =ICON.ico
