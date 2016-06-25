

// Project
#include "IntermodDataTest.h"
#include "IntermodMeasurementTest.h"

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
    testRunner.addTest(new IntermodDataTest);
    testRunner.addTest(new IntermodMeasurementTest(connectionType, address));

    qDebug() << "Global result: " << (testRunner.runTests() ? "PASS" : "FAIL");
    return 0;
}
