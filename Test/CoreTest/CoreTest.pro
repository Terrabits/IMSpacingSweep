QT      += core gui widgets testlib
TEMPLATE = app
TARGET   = CoreTest
CONFIG  += testcase

include(../../Core/core.pri)
HEADERS += IntermodWidgetTest.h \
           IntermodTraceTest.h \
           TracesWidgetTest.h \
           IntermodTraceModelTest.h \
           IntermodTraceDelegateTest.h \
           FrequencyConversionTest.h \
           IntermodChannelsTest.h \
           ProcessTracesTest.h \
    CombinerTest.h
SOURCES += main.cpp \
           IntermodWidgetTest.cpp \
           IntermodTraceTest.cpp \
           TracesWidgetTest.cpp \
           IntermodTraceModelTest.cpp \
           IntermodTraceDelegateTest.cpp \
           FrequencyConversionTest.cpp \
           IntermodChannelsTest.cpp \
           ProcessTracesTest.cpp \
    CombinerTest.cpp

DEFINES += SOURCE_DIR=\\\"$$PWD/\\\"


