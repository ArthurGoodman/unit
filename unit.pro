TEMPLATE = lib
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += staticlib

SOURCES += \
    testset.cpp \
    testrunner.cpp \
    itest.cpp \
    testcollection.cpp \
    literalmatchtest.cpp \
    functiontest.cpp \
    basictest.cpp \
    test.cpp

HEADERS += \
    testset.h \
    testrunner.h \
    itest.h \
    testcollection.h \
    literalmatchtest.h \
    functiontest.h \
    basictest.h \
    test.h
