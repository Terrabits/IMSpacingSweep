QT      += core gui widgets testlib
TEMPLATE = app
TARGET   = Test
CONFIG  += testcase

include(../Core/core.pri)
HEADERS += \
    IntermodMeasurementTest.h \
    IntermodDataTest.h \
    IntermodWidgetTest.h
SOURCES += main.cpp \
    IntermodMeasurementTest.cpp \
    IntermodDataTest.cpp \
    IntermodWidgetTest.cpp

DEFINES += SOURCE_DIR=\\\"$$PWD/\\\"


