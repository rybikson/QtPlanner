#-------------------------------------------------
#
# Project created by QtCreator 2013-06-27T21:00:59
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtPlanner
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    eventtemplate.cpp \
    eventmodel.cpp \
    eventset.cpp \
    filehandler.cpp \
    dataset.cpp \
    downloader.cpp \
    about.cpp \
    help.cpp \
    settings.cpp

HEADERS  += mainwindow.h \
    eventtemplate.h \
    eventmodel.h \
    eventset.h \
    filehandler.h \
    dataset.h \
    downloader.h \
    about.h \
    help.h \
    settings.h

FORMS    += mainwindow.ui \
    eventtemplate.ui \
    about.ui \
    help.ui \
    settings.ui
