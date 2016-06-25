QT      += core gui widgets testlib
TEMPLATE = app
TARGET   = Test
CONFIG  += testcase

include(../Core/core.pri)
HEADERS += \
    IntermodMeasurementTest.h \
    IntermodDataTest.h
SOURCES += main.cpp \
    IntermodMeasurementTest.cpp \
    IntermodDataTest.cpp

DEFINES += SOURCE_DIR=\\\"$$PWD/\\\"


