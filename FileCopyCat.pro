QT += core
QT -= gui

CONFIG += c++11

TARGET = FilesCopyCat
#CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    copy.cpp

HEADERS += \
    copy.h

RESOURCES +=

RC_ICONS = cat.ico
