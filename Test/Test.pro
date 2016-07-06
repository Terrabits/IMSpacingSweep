QT      += core gui widgets testlib
TEMPLATE = app
TARGET   = Test
CONFIG  += testcase

include(../Core/core.pri)
HEADERS += \
    IntermodMeasurementTest.h \
    IntermodDataTest.h \
    IntermodWidgetTest.h \
    IntermodTraceTest.h
SOURCES += main.cpp \
    IntermodMeasurementTest.cpp \
    IntermodDataTest.cpp \
    IntermodWidgetTest.cpp \
    IntermodTraceTest.cpp

DEFINES += SOURCE_DIR=\\\"$$PWD/\\\"


