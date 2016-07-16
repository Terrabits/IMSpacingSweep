QT      += core gui widgets testlib
TEMPLATE = app
TARGET   = Test
CONFIG  += testcase

include(../Core/core.pri)
HEADERS += \
    IntermodMeasurementTest.h \
    IntermodDataTest.h \
    IntermodWidgetTest.h \
    IntermodTraceTest.h \
    WriteIntermodTraceTest.h \
    TracesWidgetTest.h \
    IntermodTraceModelTest.h \
    IntermodTraceDelegateTest.h
SOURCES += main.cpp \
    IntermodMeasurementTest.cpp \
    IntermodDataTest.cpp \
    IntermodWidgetTest.cpp \
    IntermodTraceTest.cpp \
    WriteIntermodTraceTest.cpp \
    TracesWidgetTest.cpp \
    IntermodTraceModelTest.cpp \
    IntermodTraceDelegateTest.cpp

DEFINES += SOURCE_DIR=\\\"$$PWD/\\\"


