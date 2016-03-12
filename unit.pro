TEMPLATE = lib
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += staticlib

SOURCES += \
    test.cpp \
    testmanager.cpp

HEADERS += \
    test.h \
    testmanager.h
