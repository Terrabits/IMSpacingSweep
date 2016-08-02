

// Project
#include "FrequencyConversionTest.h"
#include "IntermodDataTest.h"
#include "IntermodMeasurementTest.h"
#include "IntermodTraceDelegateTest.h"
#include "IntermodTraceModelTest.h"
#include "IntermodTraceTest.h"
#include "IntermodWidgetTest.h"
#include "TracesWidgetTest.h"
#include "WriteIntermodTraceTest.h"

// RsaToolbox
#include <Definitions.h>
#include <TestRunner.h>
using namespace RsaToolbox;

// Qt
#include <QApplication>
#include <QTest>
#include <QDebug>


int main(int argc, char *argv[])
{
     RsaToolbox::ConnectionType connectionType = RsaToolbox::ConnectionType::VisaTcpSocketConnection;
     QString address = "127.0.0.1::5025";

    TestRunner testRunner;
    if (argc == 2) {
        QString arg(argv[1]);
        arg = arg.remove("-").toLower();
        if (arg == "intermodwidget") {
            testRunner.addTest(new IntermodWidgetTest(connectionType, address));
        }
        else if (arg == "traceswidget") {
            testRunner.addTest(new TracesWidgetTest(connectionType, address));
        }
        else if (arg == "writeintermodtrace") {
            testRunner.addTest(new WriteIntermodTraceTest(connectionType, address));
        }
    }
    else {
        testRunner.addTest(new IntermodDataTest);
        testRunner.addTest(new FrequencyConversionTest);
        testRunner.addTest(new IntermodMeasurementTest(connectionType, address));
        testRunner.addTest(new IntermodTraceTest);
        testRunner.addTest(new IntermodTraceModelTest);
        testRunner.addTest(new IntermodTraceDelegateTest);
    }

    bool passed = testRunner.runTests();
    if (passed) {
        qDebug() << "Global result: PASS";
        return 0;
    }
    else {
        qDebug() << "Global result: FAIL";
        return -1;
    }
}
