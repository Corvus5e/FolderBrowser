#-------------------------------------------------
#
# Project created by QtCreator 2017-01-13T16:53:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FolderBrowserGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    renderarea.cpp \
    foldertree.cpp

HEADERS  += mainwindow.h \
    renderarea.h \
    foldertree.h

FORMS    += mainwindow.ui
