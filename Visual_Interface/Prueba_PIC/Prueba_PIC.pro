#-------------------------------------------------
#
# Project created by QtCreator 2017-04-20T16:59:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Prueba_PIC
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    hid.c

HEADERS  += mainwindow.h \
    hidapi.h

FORMS    += mainwindow.ui
LIBS     += -lsetupapi
