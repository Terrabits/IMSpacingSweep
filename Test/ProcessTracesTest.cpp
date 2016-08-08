#include "ProcessTracesTest.h"


// Project
#include "IntermodSettings.h"
#include "IntermodTrace.h"
#include "ProcessTraces.h"

// RsaToolbox
#include "Test.h"
using namespace RsaToolbox;


typedef QList<IntermodTrace> Traces;
Q_DECLARE_METATYPE(Traces)
Q_DECLARE_METATYPE(IntermodSettings)

ProcessTracesTest::ProcessTracesTest(RsaToolbox::ConnectionType type, const QString &address, QObject *parent) :
    VnaTestClass(type, address, parent)
{

}

ProcessTracesTest::~ProcessTracesTest()
{

}

void ProcessTracesTest::initTestCase() {
    _applicationName = "Process Traces Test";
    _version         = "0.0";

    // Test results path
    _logDir.setPath(SOURCE_DIR);
    QString path = "ProcessTracesTest";
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

    _logFilenames << "1 - Preprocess oip3m.txt"
                  << "2 - Preprocess iip5l.txt"
                  << "3 - Empty Calibration.txt"
                  << "4 - Full Calibration.txt"
                  << "5 - Run oip3m.txt"
                  << "6 - Run Full.txt";

    VnaTestClass::_initTestCase();
}

void ProcessTracesTest::preprocess_data() {
    QTest::addColumn<Traces>("before");
    QTest::addColumn<Traces>("after" );


    // IP3MO ->
    // - LTO
    // - IM3LO
    // - IM3UO
    // - IP3MO
    Traces before;
    before << IntermodTrace(TraceType::outputIntercept, TraceFeature::major, 3);

    Traces after;
    after  << IntermodTrace(TraceType::outputTone, TraceFeature::lower);
    after  << IntermodTrace(TraceType::intermod,   TraceFeature::lower, 3);
    after  << IntermodTrace(TraceType::intermod,   TraceFeature::upper, 3);
    after  << IntermodTrace(TraceType::outputIntercept, TraceFeature::major, 3);

    QTest::newRow("oip3m") << before << after;

    // IP5LI ->
    // - LTI
    // - LTO
    // - IM5LO
    // - IP5LI
    before.clear();
    before << IntermodTrace(TraceType::inputIntercept, TraceFeature::lower, 5);

    after.clear();
    after  << IntermodTrace(TraceType::inputTone,      TraceFeature::lower   );
    after  << IntermodTrace(TraceType::outputTone,     TraceFeature::lower   );
    after  << IntermodTrace(TraceType::intermod,       TraceFeature::lower, 5);
    after  << IntermodTrace(TraceType::inputIntercept, TraceFeature::lower, 5);

    QTest::newRow("iip5l") << before << after;
}
void ProcessTracesTest::preprocess() {
    QFETCH(Traces, before);
    QFETCH(Traces, after) ;

    IntermodSettings settings;
    const uint base = 1;
    ProcessTraces pt(before, settings, _vna.data(), base);
    QCOMPARE(after, pt._traces);
}

void ProcessTracesTest::calibration_data() {
    QTest::addColumn<IntermodSettings>("settings");
    QTest::addColumn<Traces>          ("traces"  );

    // No traces
    //   - should still calibrate original tones
    VnaIntermod::ToneSource upperSource;
    upperSource.setPort(3);

    IntermodSettings settings;
    settings.setLowerSourcePort(1);
    settings.setUpperSource(upperSource);
    settings.setReceivingPort(2);
    settings.setCenterFrequency(1, SiPrefix::Giga);
    settings.setStartToneDistance(10, SiPrefix::Mega);
    settings.setStopToneDistance(100, SiPrefix::Mega);
    settings.setPoints(10);
    settings.setPower(-5);
    settings.setIfBw(1, SiPrefix::Kilo);

    Traces traces;
    QTest::newRow("empty") << settings << traces;

    // Everything
    // - LTI
    // - LTO
    // - UTI
    // - UTO
    // - IM3MO
    // - IM5MO
    // - IM7MO
    // - IM9MO
    traces.clear();
    traces << IntermodTrace(TraceType::inputTone , TraceFeature::lower   );
    traces << IntermodTrace(TraceType::outputTone, TraceFeature::lower   );
    traces << IntermodTrace(TraceType::inputTone , TraceFeature::upper   );
    traces << IntermodTrace(TraceType::outputTone, TraceFeature::upper   );
    traces << IntermodTrace(TraceType::intermod  , TraceFeature::major, 3);
    traces << IntermodTrace(TraceType::intermod  , TraceFeature::major, 5);
    traces << IntermodTrace(TraceType::intermod  , TraceFeature::major, 7);
    traces << IntermodTrace(TraceType::intermod  , TraceFeature::major, 9);
    QTest::newRow("full") << settings << traces;
}
void ProcessTracesTest::calibration() {
    QFETCH(IntermodSettings, settings);
    QFETCH(Traces,           traces);

    const uint base = 1;
    ProcessTraces pt(traces, settings, _vna.data(), base);
    pt.setupCalibration();
    _vna->settings().displayOn();
    pause("Calibration: Check setup");
    _vna->settings().displayOff();
    QVERIFY(!_vna->isError());
}

void ProcessTracesTest::run_data() {
    QTest::addColumn<IntermodSettings>("settings" );
    QTest::addColumn<Traces>          ("traces");

    // IP3MO ->
    // - LTO
    // - IM3LO
    // - IM3UO
    // - IP3MO
    VnaIntermod::ToneSource upperSource;
    upperSource.setPort(3);

    IntermodSettings settings;
    settings.setLowerSourcePort(1);
    settings.setUpperSource(upperSource);
    settings.setReceivingPort(2);
    settings.setCenterFrequency(1, SiPrefix::Giga);
    settings.setStartToneDistance(10, SiPrefix::Mega);
    settings.setStopToneDistance(100, SiPrefix::Mega);
    settings.setPoints(10);
    settings.setPower(-5);
    settings.setIfBw(1, SiPrefix::Kilo);

    Traces traces;
    traces << IntermodTrace(TraceType::outputIntercept, TraceFeature::major, 3);
    QTest::newRow("oip3m") << settings << traces;

    // Full (52 traces)
    // - LTI
    // - LTO
    // - UTI
    // - UTO
    // - IM3LO
    // - IM3UO
    // - IM3MO
    // - IM5LO
    // - IM5UO
    // - IM5MO
    // - IM7LO
    // - IM7UO
    // - IM7MO
    // - IM9LO
    // - IM9UO
    // - IM9MO
    // - IM3MLOR
    // - IM3MUOR
    // - IM3MMOR
    // - IM5MLOR
    // - IM5MUOR
    // - IM5MMOR
    // - IM7MLOR
    // - IM7MUOR
    // - IM7MMOR
    // - IM9MLOR
    // - IM9MUOR
    // - IM9MMOR
    // - IP3MLOR
    // - IP3MUOR
    // - IP3MMOR
    // - IP3MLIR
    // - IP3MUIR
    // - IP3MMIR
    // - IP5MLOR
    // - IP5MUOR
    // - IP5MMOR
    // - IP5MLIR
    // - IP5MUIR
    // - IP5MMIR
    // - IP7MLOR
    // - IP7MUOR
    // - IP7MMOR
    // - IP7MLIR
    // - IP7MUIR
    // - IP7MMIR
    // - IP9MLOR
    // - IP9MUOR
    // - IP9MMOR
    // - IP9MLIR
    // - IP9MUIR
    // - IP9MMIR
    traces.clear();
    traces << IntermodTrace(TraceType::inputTone , TraceFeature::lower   );
    traces << IntermodTrace(TraceType::outputTone, TraceFeature::lower   );
    traces << IntermodTrace(TraceType::inputTone , TraceFeature::upper   );
    traces << IntermodTrace(TraceType::outputTone, TraceFeature::upper   );

    traces << IntermodTrace(TraceType::intermod,   TraceFeature::lower, 3);
    traces << IntermodTrace(TraceType::intermod,   TraceFeature::upper, 3);
    traces << IntermodTrace(TraceType::intermod,   TraceFeature::major, 3);
    traces << IntermodTrace(TraceType::intermod,   TraceFeature::lower, 5);
    traces << IntermodTrace(TraceType::intermod,   TraceFeature::upper, 5);
    traces << IntermodTrace(TraceType::intermod,   TraceFeature::major, 5);
    traces << IntermodTrace(TraceType::intermod,   TraceFeature::lower, 7);
    traces << IntermodTrace(TraceType::intermod,   TraceFeature::upper, 7);
    traces << IntermodTrace(TraceType::intermod,   TraceFeature::major, 7);
    traces << IntermodTrace(TraceType::intermod,   TraceFeature::lower, 9);
    traces << IntermodTrace(TraceType::intermod,   TraceFeature::upper, 9);
    traces << IntermodTrace(TraceType::intermod,   TraceFeature::major, 9);

    traces << IntermodTrace(TraceType::relative,   TraceFeature::lower, 3);
    traces << IntermodTrace(TraceType::relative,   TraceFeature::upper, 3);
    traces << IntermodTrace(TraceType::relative,   TraceFeature::major, 3);
    traces << IntermodTrace(TraceType::relative,   TraceFeature::lower, 5);
    traces << IntermodTrace(TraceType::relative,   TraceFeature::upper, 5);
    traces << IntermodTrace(TraceType::relative,   TraceFeature::major, 5);
    traces << IntermodTrace(TraceType::relative,   TraceFeature::lower, 7);
    traces << IntermodTrace(TraceType::relative,   TraceFeature::upper, 7);
    traces << IntermodTrace(TraceType::relative,   TraceFeature::major, 7);
    traces << IntermodTrace(TraceType::relative,   TraceFeature::lower, 9);
    traces << IntermodTrace(TraceType::relative,   TraceFeature::upper, 9);
    traces << IntermodTrace(TraceType::relative,   TraceFeature::major, 9);

    traces << IntermodTrace(TraceType::inputIntercept,  TraceFeature::lower, 3);
    traces << IntermodTrace(TraceType::inputIntercept,  TraceFeature::upper, 3);
    traces << IntermodTrace(TraceType::inputIntercept,  TraceFeature::major, 3);
    traces << IntermodTrace(TraceType::outputIntercept, TraceFeature::lower, 3);
    traces << IntermodTrace(TraceType::outputIntercept, TraceFeature::upper, 3);
    traces << IntermodTrace(TraceType::outputIntercept, TraceFeature::major, 3);

    traces << IntermodTrace(TraceType::inputIntercept,  TraceFeature::lower, 5);
    traces << IntermodTrace(TraceType::inputIntercept,  TraceFeature::upper, 5);
    traces << IntermodTrace(TraceType::inputIntercept,  TraceFeature::major, 5);
    traces << IntermodTrace(TraceType::outputIntercept, TraceFeature::lower, 5);
    traces << IntermodTrace(TraceType::outputIntercept, TraceFeature::upper, 5);
    traces << IntermodTrace(TraceType::outputIntercept, TraceFeature::major, 5);

    traces << IntermodTrace(TraceType::inputIntercept,  TraceFeature::lower, 7);
    traces << IntermodTrace(TraceType::inputIntercept,  TraceFeature::upper, 7);
    traces << IntermodTrace(TraceType::inputIntercept,  TraceFeature::major, 7);
    traces << IntermodTrace(TraceType::outputIntercept, TraceFeature::lower, 7);
    traces << IntermodTrace(TraceType::outputIntercept, TraceFeature::upper, 7);
    traces << IntermodTrace(TraceType::outputIntercept, TraceFeature::major, 7);

    traces << IntermodTrace(TraceType::inputIntercept,  TraceFeature::lower, 9);
    traces << IntermodTrace(TraceType::inputIntercept,  TraceFeature::upper, 9);
    traces << IntermodTrace(TraceType::inputIntercept,  TraceFeature::major, 9);
    traces << IntermodTrace(TraceType::outputIntercept, TraceFeature::lower, 9);
    traces << IntermodTrace(TraceType::outputIntercept, TraceFeature::upper, 9);
    traces << IntermodTrace(TraceType::outputIntercept, TraceFeature::major, 9);

    QTest::newRow("full") << settings << traces;
}
void
ProcessTracesTest::run() {
    QFETCH(IntermodSettings, settings);
    QFETCH(Traces,           traces);

    const uint base = 1;
    ProcessTraces pt(traces, settings, _vna.data(), base);
    pt.run();
    _vna->settings().displayOn();
    pause("Run: Check setup");
    _vna->settings().displayOff();
    QVERIFY(!_vna->isError());
}

void ProcessTracesTest::debugPrint(QString header, QList<IntermodTrace> traces) {
    qDebug() << header.toUpper();
    for (int i = 0; i < traces.size(); i++) {
        qDebug() << "  " << traces[i].abbreviate();
    }
}
