QT      += core gui widgets testlib
TEMPLATE = app
TARGET   = Test
CONFIG  += testcase

include(../Core/core.pri)
HEADERS += \
    IntermodWidgetTest.h \
    IntermodTraceTest.h \
    TracesWidgetTest.h \
    IntermodTraceModelTest.h \
    IntermodTraceDelegateTest.h \
    FrequencyConversionTest.h \
    IntermodChannelsTest.h \
    ProcessTracesTest.h
SOURCES += main.cpp \
    IntermodWidgetTest.cpp \
    IntermodTraceTest.cpp \
    TracesWidgetTest.cpp \
    IntermodTraceModelTest.cpp \
    IntermodTraceDelegateTest.cpp \
    FrequencyConversionTest.cpp \
    IntermodChannelsTest.cpp \
    ProcessTracesTest.cpp

DEFINES += SOURCE_DIR=\\\"$$PWD/\\\"


