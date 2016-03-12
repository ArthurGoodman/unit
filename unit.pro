TEMPLATE = lib
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += staticlib

DEFINES += UNIT

SOURCES += \
    unit.cpp

HEADERS += \
    unit.h
