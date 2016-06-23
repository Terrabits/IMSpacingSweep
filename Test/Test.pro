QT      += core gui widgets testlib
TEMPLATE = app
TARGET   = Test
CONFIG  += testcase

include(../Core/core.pri)
HEADERS += \
    IntermodMeasurementTest.h
SOURCES += main.cpp \
    IntermodMeasurementTest.cpp

DEFINES += SOURCE_DIR=\\\"$$PWD/\\\"


