#include "IntermodMeasurementTest.h"


// Project
#include "IMSettings.h"
#include "IntermodMeasurement.h"

// RsaToolbox
using namespace RsaToolbox;


IntermodMeasurementTest::IntermodMeasurementTest(ConnectionType type, const QString &address, QObject *parent) :
    VnaTestClass(type, address, parent)
{
    _applicationName = "Intermod Measurement Test";
    _version         = "0.0";

    // Test results path
    _logDir.setPath(SOURCE_DIR);
    if (isZvaFamily()) {
        QString path = "IntermodMeasurementTest/Zva/Logs";
        _logDir.mkpath(path);
        _logDir.cd(path);
    }
    else if (isZnbFamily()) {
        QString path = "IntermodMeasurementTest/Znb/Logs";
        _logDir.mkpath(path);
        _logDir.cd(path);
    }

    _logFilenames << "1 - Basic Test.txt";
}
IntermodMeasurementTest::~IntermodMeasurementTest()
{
    //
}

void IntermodMeasurementTest::basic() {
    IMSettings settings;

    IntermodMeasurement measurement(_vna.data(), 1, settings);
    IntermodError error;
    QVERIFY(measurement.isValid(error));
    QVERIFY(error.isError());
    measurement.run();

}
