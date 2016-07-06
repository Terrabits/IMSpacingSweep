#include "WriteIntermodTraceTest.h"


// Project
#include "IntermodMeasurement.h"
#include "WriteIntermodTrace.h"

// RsaToolbox
using namespace RsaToolbox;

// Qt
#include <QScopedPointer>


WriteIntermodTraceTest::WriteIntermodTraceTest(ConnectionType type, const QString &address, QObject *parent) :
    VnaTestClass(type, address, parent)
{
    _applicationName = "Write Intermod Trace Test";
    _version         = "0.0";

    // Test results path
    _logDir.setPath(SOURCE_DIR);
    QString path = "WriteIntermodTraceTest";
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

WriteIntermodTraceTest::~WriteIntermodTraceTest()
{

}

void WriteIntermodTraceTest::test() {
    // Measure
    VnaIntermod::ToneSource port3;
    port3.setPort(3);

    IntermodSettings settings;
    settings.setLowerSourcePort(1);
    settings.setUpperSource(port3);
    settings.setReceivingPort(2);
    settings.setStartCenterFrequency(1, SiPrefix::Giga);
    settings.setStopCenterFrequency( 2, SiPrefix::Giga);
    settings.setCenterFrequencyPoints(11);
    settings.setStartToneDistance(10, SiPrefix::Mega);
    settings.setStopToneDistance(100, SiPrefix::Mega);
    settings.setToneDistancePoints(10);
    settings.setPower(-10);
    settings.setIfBw(  10, SiPrefix::Kilo);
    settings.setSelectivity(VnaChannel::IfSelectivity::High);
    IntermodMeasurement measurement(_vna.data(), 1, settings);
    measurement.run();

    QScopedPointer<IntermodData> data(measurement.takeResult());
    QVERIFY(false);
}
