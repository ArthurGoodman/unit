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
    test.cpp \
    testbase.cpp

HEADERS += \
    testset.h \
    testrunner.h \
    itest.h \
    testcollection.h \
    test.h \
    testbase.h \
    function_traits.h
