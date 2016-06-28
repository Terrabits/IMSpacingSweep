#include "IntermodMeasurementTest.h"


// Project
#include "IntermodSettings.h"
#include "IntermodMeasurement.h"

// RsaToolbox
#include <VnaChannel.h>
using namespace RsaToolbox;


IntermodMeasurementTest::IntermodMeasurementTest(ConnectionType type, const QString &address, QObject *parent) :
    VnaTestClass(type, address, parent)
{
    _applicationName = "Intermod Measurement Test";
    _version         = "0.0";

    // Test results path
    _logDir.setPath(SOURCE_DIR);
    QString path = "IntermodMeasurementTest";
    _logDir.mkpath(path);
    _logDir.cd(path);
    if (isZvaFamily()) {
        path = "Zva";
    }
    else if (isZnbFamily()) {
        path = "Znb";
    }
    _logDir.mkpath(path);
    _logDir.cd(path);
    path = "Logs";
    _logDir.mkpath(path);
    _logDir.cd(path);

    _logFilenames << "1 - Basic Test.txt";
}
IntermodMeasurementTest::~IntermodMeasurementTest()
{
    //
}

void IntermodMeasurementTest::basic() {
    // Ports
    VnaIntermod::ToneSource port3;
    port3.setPort(3);

    IntermodSettings settings;
    settings.setLowerSourcePort(1);
    settings.setUpperSource(port3);
    settings.setReceivingPort(2);

    // Center frequencies
    settings.setStartCenterFrequency(1, SiPrefix::Giga);
    settings.setStopCenterFrequency( 2, SiPrefix::Giga);
    settings.setCenterFrequencyPoints(11);

    // Tone spacing/distance
    settings.setStartSpacing(10, SiPrefix::Mega);
    settings.setStopSpacing(100, SiPrefix::Mega);
    settings.setSpacingPoints(10);

    // Misc
    settings.setPower(-10);
    settings.setIfBw(  10, SiPrefix::Kilo);
    settings.setSelectivity(VnaChannel::IfSelectivity::High);

    // Validate settings
    IntermodMeasurement measurement(_vna.data(), 1, settings);
    IntermodError error;
    QVERIFY(!_vna->isError());
    bool isValid = measurement.isValid(error);
    QCOMPARE(error.message, QString());
    QCOMPARE(error.code, IntermodError::Code::None);
    QCOMPARE(isValid, true);

    // Measure
    measurement.run();
    QVERIFY(!_vna->isError());
}
