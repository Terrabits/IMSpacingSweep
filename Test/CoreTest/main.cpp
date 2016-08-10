

// Project
#include "FrequencyConversionTest.h"
#include "IntermodChannelsTest.h"
#include "IntermodTraceDelegateTest.h"
#include "IntermodTraceModelTest.h"
#include "IntermodTraceTest.h"
#include "IntermodWidgetTest.h"
#include "ProcessTracesTest.h"
#include "TracesWidgetTest.h"

// RsaToolbox
#include <Definitions.h>
#include <TestRunner.h>
using namespace RsaToolbox;

// Qt
#include <QApplication>
#include <QTest>
#include <QDebug>


int main()
{
     RsaToolbox::ConnectionType connectionType = RsaToolbox::ConnectionType::VisaTcpSocketConnection;
     QString address = "127.0.0.1::5025";

    TestRunner testRunner;
//    testRunner.addTest(new FrequencyConversionTest);
//    testRunner.addTest(new IntermodTraceTest      );
    testRunner.addTest(new IntermodTraceModelTest   );
    testRunner.addTest(new IntermodTraceDelegateTest);
//    testRunner.addTest(new IntermodChannelsTest(connectionType, address));
//    testRunner.addTest(new ProcessTracesTest   (connectionType, address));

    // Fix these:
//    testRunner.addTest(new IntermodTraceModelTest);
//    testRunner.addTest(new IntermodTraceDelegateTest);

    bool passed = testRunner.runTests();
    qDebug() << "";
    qDebug() << "-------------------";
    qDebug() << "Global pass? " << passed;
    qDebug() << "";
    return passed ? 0 : -1;
}
