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
           IntermodSettings.h \
           IntermodWidget.h \
           IntermodTrace.h \
    IntermodError.h \
    TracesWidget.h \
    IntermodTraceModel.h \
    IntermodTraceDelegate.h \
    FrequencyConversionGenerator.h \
    IntermodChannels.h \
    ProcessTraces.h \
    CalibrateWidget.h \
    ProcessTracesWidget.h \
    ProcessThread.h
SOURCES += \
           IntermodSettings.cpp \
           IntermodWidget.cpp \
           IntermodTrace.cpp \
    IntermodError.cpp \
    TracesWidget.cpp \
    IntermodTraceModel.cpp \
    IntermodTraceDelegate.cpp \
    FrequencyConversionGenerator.cpp \
    IntermodChannels.cpp \
    ProcessTraces.cpp \
    CalibrateWidget.cpp \
    ProcessTracesWidget.cpp \
    ProcessThread.cpp
FORMS   += IntermodWidget.ui \
    TracesWidget.ui \
    CalibrateWidget.ui \
    ProcessTracesWidget.ui

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

