#-------------------------------------------------
#
# Project created by QtCreator 2015-07-04T17:56:04
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = photoFix
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    color_change.cpp \
    addon.cpp

HEADERS  += widget.h \
    color_change.h \
    addon.h
