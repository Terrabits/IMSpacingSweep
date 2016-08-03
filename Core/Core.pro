#-------------------------------------------------
# Generated from:
# Rohde & Schwarz Vna Macro Template
# (C) 2016 Rohde & Schwarz North America
#
# Requires Qt 5
# Project created by QtCreator <%= Time.zone.now %>
#
#-------------------------------------------------

# Project Settings
QT           += core gui widgets
TEMPLATE      = lib
CONFIG       += staticlib
DESTDIR       = $$PWD/Library
TARGET = Core
CONFIG(debug, debug|release) {
       TARGET = $$join(TARGET,,,d)
}

# Files
include(../RsaToolbox/rsatoolbox.pri)
HEADERS += Settings.h \
           Measurement.h \
           Measure.h \
           IntermodMeasurement.h \
           IntermodSettings.h \
           IntermodData.h \
           IntermodWidget.h \
           TraceSettings.h \
           IntermodTrace.h \
    WriteIntermodTrace.h \
    IntermodFunctions.h \
    IntermodError.h \
    TracesWidget.h \
    IntermodTraceModel.h \
    IntermodTraceDelegate.h \
    FrequencyConversion.h \
    FrequencyConversionGenerator.h \
    IntermodChannels.h
SOURCES += Measurement.cpp \
           Measure.cpp \
           IntermodMeasurement.cpp \
           IntermodSettings.cpp \
           IntermodData.cpp \
           IntermodWidget.cpp \
           TraceSettings.cpp \
           IntermodTrace.cpp \
    WriteIntermodTrace.cpp \
    IntermodFunctions.cpp \
    IntermodError.cpp \
    TracesWidget.cpp \
    IntermodTraceModel.cpp \
    IntermodTraceDelegate.cpp \
    FrequencyConversion.cpp \
    FrequencyConversionGenerator.cpp \
    IntermodChannels.cpp
FORMS   += IntermodWidget.ui \
    TracesWidget.ui

# Defines
DEFINES += SOURCE_DIR=\\\"$$PWD\\\"
CONFIG(debug, debug|release) {
    DEFINES += DEBUG_MODE
}
CONFIG(release, debug|release) {
    DEFINES += QT_NO_DEBUG_OUTPUT
}

# OS Specific
## Windows
win32 {
    # Windows macros
}

## Mac
macx {
    # Mac-ros :-P
}

