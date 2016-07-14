#include "IntermodMeasurementTest.h"


// Project
#include "IntermodSettings.h"
#include "IntermodMeasurement.h"

// RsaToolbox
#include <VnaChannel.h>
using namespace RsaToolbox;

// Qt
#include <QDebug>
#include <QSignalSpy>


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

    _logFilenames << "1 - Basic test.txt";
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
    double startCenter  =  1.0E9;
    double stopCenter   =  2.0E9;
    uint   centerPoints = 11;
    settings.setStartCenterFrequency(startCenter);
    settings.setStopCenterFrequency( stopCenter);
    settings.setCenterFrequencyPoints(centerPoints);

    // Tone spacing/distance
    double startDistance  =  10.0E6;
    double stopDistance   = 100.0E6;
    uint   distancePoints =  10;
    settings.setStartToneDistance(startDistance);
    settings.setStopToneDistance(stopDistance);
    settings.setToneDistancePoints(distancePoints);

    // Misc
    settings.setPower(-10);
    settings.setIfBw ( 10, SiPrefix::Kilo);
    settings.setSelectivity(VnaChannel::IfSelectivity::High);

    // Traces
    const uint maxOrder = 9;
    SharedIntermodTrace trace(new IntermodTrace);
    trace->setName("test");
    trace->setY   ("IM9 Major");
    trace->setX   ("Tone Distance");
    trace->setAt  ("Center Frequency");
    trace->setAtValue(settings.startCenterFrequency_Hz());

    SharedIntermodTraces traces;
    traces << trace;

    // Validate settings
    const uint refChannel = 1;
    IntermodMeasurement measurement(_vna.data(), refChannel, settings, traces);
    QSignalSpy starting(&measurement, SIGNAL(starting()));
    QSignalSpy progress(&measurement, SIGNAL(progress(uint)));
    QSignalSpy finished(&measurement, SIGNAL(finished()));

    IntermodError error;
    QVERIFY(!_vna->isError());
    bool isValid = measurement.isValid(error);
    QCOMPARE(error.message, QString());
    QCOMPARE(error.code, IntermodError::Code::None);
    QCOMPARE(isValid, true);

    // Measure
    measurement.run();
    QVERIFY(!_vna->isError());

    const int percents = settings.toneDistancePoints() + 1;
    QCOMPARE(starting.count(),        1);
    QCOMPARE(finished.count(),        1);
    QCOMPARE(progress.count(), percents);
    QCOMPARE(progress.first().first().toUInt(), uint(  0));
    QCOMPARE(progress.last() .first().toUInt(), uint(100));

    QScopedPointer<IntermodData> data(measurement.takeResult());
    QVERIFY(!data->isEmpty());
    QCOMPARE(data->maxOrder(), maxOrder);

    // Tones
    testMatrix(data->lowerToneAtInput,  distancePoints, centerPoints);
    testMatrix(data->upperToneAtInput,  distancePoints, centerPoints);
    testMatrix(data->lowerToneAtOutput, distancePoints, centerPoints);
    testMatrix(data->upperToneAtOutput, distancePoints, centerPoints);

    // IM3
    testMatrix(data->intermod3Lower, distancePoints, centerPoints);
    testMatrix(data->intermod3Upper, distancePoints, centerPoints);
    testMatrix(data->intermod3Major, distancePoints, centerPoints);

    // IM5
    testMatrix(data->intermod5Lower, distancePoints, centerPoints);
    testMatrix(data->intermod5Upper, distancePoints, centerPoints);
    testMatrix(data->intermod5Major, distancePoints, centerPoints);

    // IM7
    testMatrix(data->intermod7Lower, distancePoints, centerPoints);
    testMatrix(data->intermod7Upper, distancePoints, centerPoints);
    testMatrix(data->intermod7Major, distancePoints, centerPoints);

    // IM9
    testMatrix(data->intermod9Lower, distancePoints, centerPoints);
    testMatrix(data->intermod9Upper, distancePoints, centerPoints);
    testMatrix(data->intermod9Major, distancePoints, centerPoints);

    // IP
    testMatrix(data->intercept3Major, distancePoints, centerPoints);
    testMatrix(data->intercept5Major, distancePoints, centerPoints);
    testMatrix(data->intercept7Major, distancePoints, centerPoints);
    testMatrix(data->intercept9Major, distancePoints, centerPoints);
}

void IntermodMeasurementTest::testMatrix(ComplexMatrix2D &m, uint rows, uint columns) {
    QCOMPARE(m.size(), rows);
    for (uint i = 0; i < rows; i++) {
        QCOMPARE(m[i].size(), columns);
    }
}
