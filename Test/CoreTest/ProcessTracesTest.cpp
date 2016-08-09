#include "ProcessTracesTest.h"


// Project
#include "IntermodError.h"
#include "IntermodSettings.h"
#include "IntermodTrace.h"
#include "ProcessTraces.h"

// RsaToolbox
#include "General.h"
#include "Test.h"
using namespace RsaToolbox;

// Qt
#include <Qt>


typedef QList<IntermodTrace> Traces;
typedef IntermodError::Code Code;
Q_DECLARE_METATYPE(Traces)
Q_DECLARE_METATYPE(IntermodSettings)
Q_DECLARE_METATYPE(Code)

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

    _logFilenames << "1  - Is ready.txt"
                  << "2  - Low port is zero.txt"
                  << "3  - Low port too high.txt"
                  << "4  - Upper port is zero.txt"
                  << "5  - Upper port too high.txt"
                  << "6  - Recv port is zero.txt"
                  << "7  - Recv port too high.txt"
                  << "8  - Center freq too low.txt"
                  << "9  - Center freq too high.txt"
                  << "10 - Start too low.txt"
                  << "11 - Td too low.txt"
                  << "12 - Start too high.txt"
                  << "13 - Stop too low.txt"
                  << "14 - Stop too high.txt"
                  << "15 - Td too high.txt"
                  << "16 - No points.txt"
                  << "17 - Too many points.txt"
                  << "18 - Power too low.txt"
                  << "19 - Power too high.txt"
                  << "20 - IF BW too low.txt"
                  << "21 - IF BW too high.txt"
                  << "22 - Channel not found.txt"
                  << "23 - No traces.txt"
                  << "24 - IM3 too low.txt"
                  << "25 - IM5 too low.txt"
                  << "26 - IM7 too low.txt"
                  << "27 - IM9 too low.txt"
                  << "28 - IM3 too high.txt"
                  << "29 - IM5 too high.txt"
                  << "30 - IM7 too high.txt"
                  << "31 - IM9 too high.txt"
                  << "32 - Preprocess oip3m.txt"
                  << "33 - Preprocess iip5l.txt"
                  << "34 - Empty Calibration.txt"
                  << "35 - Full Calibration.txt"
                  << "36 - Run oip3m.txt"
                  << "37 - Run All Traces.txt"
                  << "38 - Trace Math.txt";

    VnaTestClass::_initTestCase();

    _vna.reset(new Vna(_connectionType, _address));
    _vnaMax_Hz = _vna->properties().maximumFrequency_Hz();
    _vnaMin_Hz = _vna->properties().minimumFrequency_Hz();
    _vna.reset();
}

void ProcessTracesTest::ready_data() {
    QTest::addColumn<IntermodSettings>("settings");
    QTest::addColumn<Traces>("traces");
    QTest::addColumn<IntermodError::Code>("errorCode");

    // Correct settings
    // to start from
    VnaIntermod::ToneSource upperSource;
    upperSource.setPort(3);

    IntermodSettings settings;
    settings.setLowerSourcePort(1);
    settings.setUpperSource    (upperSource);
    settings.setReceivingPort  (2);
    settings.setCenterFrequency  (  1, SiPrefix::Giga);
    settings.setStartToneDistance( 10, SiPrefix::Mega);
    settings.setStopToneDistance (100, SiPrefix::Mega);
    settings.setPoints(10);
    settings.setPower (-5);
    settings.setIfBw  (1, SiPrefix::Kilo);
    settings.setSelectivity(VnaChannel::IfSelectivity::High);
    settings.setChannel(1);

    Traces traces;
    traces << IntermodTrace(TraceType::intermod, TraceFeature::major, 3);

    // No error [1]
    QTest::newRow("NoError") << settings << traces << Code::None;

    // Lower port [2, 3]
    settings.setLowerSourcePort(0);
    QTest::newRow("LowPortIsZero")  << settings << traces << Code::LowerSourcePort;
    settings.setLowerSourcePort(100);
    QTest::newRow("LowPortTooHigh") << settings << traces << Code::LowerSourcePort;
    settings.setLowerSourcePort(1);

    // Upper port [4, 5]
    upperSource.setPort(0);
    settings.setUpperSource(upperSource);
    QTest::newRow("UpperPortIsZero")  << settings << traces << Code::UpperSource;
    upperSource.setPort(100);
    settings.setUpperSource(upperSource);
    QTest::newRow("UpperPortTooHigh") << settings << traces << Code::UpperSource;
    upperSource.setPort(3);
    settings.setUpperSource(upperSource);

    // Receiving port [6, 7]
    settings.setReceivingPort(0);
    QTest::newRow("RecvPortIsZero") << settings << traces << Code::ReceivingPort;
    settings.setReceivingPort(100);
    QTest::newRow("RecvPortTooHigh") << settings << traces << Code::ReceivingPort;
    settings.setReceivingPort(2);

    // Center frequency [8, 9]
    settings.setCenterFrequency(0);
    QTest::newRow("CenterFreqTooLow") << settings << traces << Code::CenterFrequency;
    settings.setCenterFrequency(1, SiPrefix::Tera);
    QTest::newRow("CenterFreqTooHigh") << settings << traces << Code::CenterFrequency;
    settings.setCenterFrequency(1, SiPrefix::Giga);

    // Start tone [10, 11, 12]
    settings.setStartToneDistance(0);
    QTest::newRow("StartTooLow") << settings << traces << Code::StartToneDistance;
    settings.setStopToneDistance(1);
    QTest::newRow("TDTooLow") << settings << traces << Code::StartToneDistance;
    settings.setStopToneDistance(100, SiPrefix::Mega);
    settings.setStartToneDistance(200, SiPrefix::Mega);
    QTest::newRow("StartTooHigh") << settings << traces << Code::StartToneDistance;
    settings.setStartToneDistance(10, SiPrefix::Mega);

    // Stop tone [13, 14, 15]
    settings.setStopToneDistance (  0);
    QTest::newRow("StopTooLow") << settings << traces << Code::StopToneDistance;
    settings.setStopToneDistance (  1, SiPrefix::Tera);
    QTest::newRow("StopTooHigh") << settings << traces << Code::StopToneDistance;
    settings.setStartToneDistance(999, SiPrefix::Giga);
    QTest::newRow("TDTooHigh" ) << settings << traces << Code::StopToneDistance;
    settings.setStartToneDistance( 10, SiPrefix::Mega);
    settings.setStopToneDistance (100, SiPrefix::Mega);

    // Points [16, 17]
    settings.setPoints(0);
    QTest::newRow("ZeroPoints") << settings << traces << Code::Points;
    settings.setPoints(100e6);
    QTest::newRow("TooManyPoints") << settings << traces << Code::Points;
    settings.setPoints(10);

    // Power [18, 19]
    settings.setPower(-1.0e6);
    QTest::newRow("PowerTooLow") << settings << traces << Code::Power;
    settings.setPower(1.0e6);
    QTest::newRow("PowerTooHigh") << settings << traces << Code::Power;
    settings.setPower(-5);

    // IF BW [20, 21]
    settings.setIfBw(0);
    QTest::newRow("IfBwTooLow") << settings << traces << Code::IfBw;
    settings.setIfBw(1, SiPrefix::Tera);
    QTest::newRow("IfBwTooHigh") << settings << traces << Code::IfBw;
    settings.setIfBw(1, SiPrefix::Kilo);

    // Selectivity?
    // Enum, can't be wrong!

    // Channel [22]
    settings.setChannel(0);
    QTest::newRow("ChannelNotFound") << settings << traces << Code::Channel;

    // Traces [23]
    traces.clear();
    QTest::newRow("NoTraces") << settings << traces << Code::Traces;

    // Trace frequency [24..31]
    const double tdStart = 10.0e6; // 10 MHz
    settings.setCenterFrequency(_vnaMin_Hz + (3.0/2.0)*tdStart - 1.0e6);
    traces << IntermodTrace(TraceType::intermod, TraceFeature::lower, 3);
    QTest::newRow("3TooLow") << settings << traces << Code::Order;
    settings.setCenterFrequency(_vnaMin_Hz + (5.0/2.0)*tdStart - 1.0e6);
    traces.last().setOrder(5);
    QTest::newRow("5TooLow") << settings << traces << Code::Order;
    settings.setCenterFrequency(_vnaMin_Hz + (7.0/2.0)*tdStart - 1.0e6);
    traces.last().setOrder(7);
    QTest::newRow("7TooLow") << settings << traces << Code::Order;
    settings.setCenterFrequency(_vnaMin_Hz + (9.0/2.0)*tdStart - 1.0e6);
    traces.last().setOrder(9);
    QTest::newRow("9TooLow") << settings << traces << Code::Order;
    settings.setCenterFrequency(_vnaMax_Hz - (3.0/2.0)*tdStart - 1.0e6);
    traces.last().setFeature(TraceFeature::upper);
    traces.last().setOrder(3);
    QTest::newRow("3TooHigh") << settings << traces << Code::Order;
    settings.setCenterFrequency(_vnaMax_Hz - (5.0/2.0)*tdStart + 1.0e6);
    traces.last().setOrder(5);
    QTest::newRow("5TooHigh") << settings << traces << Code::Order;
    settings.setCenterFrequency(_vnaMax_Hz - (7.0/2.0)*tdStart + 1.0e6);
    traces.last().setOrder(7);
    QTest::newRow("7TooHigh") << settings << traces << Code::Order;
    settings.setCenterFrequency(_vnaMax_Hz - (9.0/2.0)*tdStart + 1.0e6);
    traces.last().setOrder(9);
    QTest::newRow("9TooHigh") << settings << traces << Code::Order;
}
void ProcessTracesTest::ready() {
    QFETCH(IntermodSettings, settings);
    QFETCH(Traces, traces);
    QFETCH(IntermodError::Code, errorCode);

//    ProcessTraces pt(traces, settings, _vna.data(), /*channel=*/ 1);
//    IntermodError error;
//    bool isReady = pt.isReady(error);
//    QCOMPARE(error.code, errorCode);
//    if (error.isError()) {
//        QVERIFY(!isReady);
//        QVERIFY(!error.message.isEmpty());
//    }
//    else {
//        QVERIFY(isReady);
//        QVERIFY(error.message.isEmpty());
//    }
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
    settings.setChannel(1);
    ProcessTraces pt(before, settings, _vna.data());
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

    settings.setChannel(1);
    ProcessTraces pt(traces, settings, _vna.data());
    pt.setupCalibration();
    _vna->settings().displayOn();
//    pause("Calibration: Check setup");
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
    traces << IntermodTrace(TraceType::outputTone,      TraceFeature::lower);
    traces << IntermodTrace(TraceType::intermod,        TraceFeature::lower, 3);
    traces << IntermodTrace(TraceType::intermod,        TraceFeature::upper, 3);
    traces << IntermodTrace(TraceType::outputIntercept, TraceFeature::major, 3);
    QTest::newRow("oip3m") << settings << traces;

    // All traces (52 traces)
    traces = allTraces();
    QTest::newRow("all_traces") << settings << traces;
}
void ProcessTracesTest::run() {
    QFETCH(IntermodSettings, settings);
    QFETCH(Traces,           traces);

    settings.setChannel(1);
    ProcessTraces pt(traces, settings, _vna.data());
    pt.run();
    QVERIFY(!_vna->isError());
    QCOMPARE(_vna->traces().size(), traces.size());
    _vna->settings().displayOn();
//    pause("Run: Check setup");
    _vna->settings().displayOff();
}

void ProcessTracesTest::traceMath() {
    // Settings
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

    settings.setChannel(1);
    ProcessTraces pt(allTraces(), settings, _vna.data());
    IntermodError error;
    bool isReady = pt.isReady(error);
    QCOMPARE(error.message, QString());
    QVERIFY(isReady);
    QVERIFY(!error.isError());

    pt.run();
    QVERIFY(!_vna->isError());

    // Sweep
    const uint time_ms = _vna->sweepTime_ms();
    _vna->manualSweepOn();
    _vna->startSweeps();
    _vna->pause(2 * time_ms + 5000);
    _vna->trace("lto_im_ch1").createMarker(1);
    _vna->trace("lto_im_ch1").marker(1).setX(750, SiPrefix::Mega);
    _vna->trace("lto_im_ch1").coupleMarkers();

    foreach(const double f, pt.fb_Hz()) {
        _vna->trace("lto_im_ch1").marker(1).setX(f);

        const double lto    = getMarkerValue("lto");
        const double lti    = getMarkerValue("lti");
//        const double uto    = getMarkerValue("uto");
//        const double uti    = getMarkerValue("uti");

        const double im3lo  = getMarkerValue("im3lo");
        const double im3uo  = getMarkerValue("im3uo");
        const double im3mo  = getMarkerValue("im3mo");
        const double im5lo  = getMarkerValue("im5lo");
        const double im5uo  = getMarkerValue("im5uo");
        const double im5mo  = getMarkerValue("im5mo");
        const double im7lo  = getMarkerValue("im7lo");
        const double im7uo  = getMarkerValue("im7uo");
        const double im7mo  = getMarkerValue("im7mo");
        const double im9lo  = getMarkerValue("im9lo");
        const double im9uo  = getMarkerValue("im9uo");
        const double im9mo  = getMarkerValue("im9mo");

        const double im3lor = getMarkerValue("im3lor");
        const double im3uor = getMarkerValue("im3uor");
        const double im3mor = getMarkerValue("im3mor");
        const double im5lor = getMarkerValue("im5lor");
        const double im5uor = getMarkerValue("im5uor");
        const double im5mor = getMarkerValue("im5mor");
        const double im7lor = getMarkerValue("im7lor");
        const double im7uor = getMarkerValue("im7uor");
        const double im7mor = getMarkerValue("im7mor");
        const double im9lor = getMarkerValue("im9lor");
        const double im9uor = getMarkerValue("im9uor");
        const double im9mor = getMarkerValue("im9mor");

        const double ip3lo  = getMarkerValue("ip3lo");
        const double ip3uo  = getMarkerValue("ip3uo");
        const double ip3mo  = getMarkerValue("ip3mo");
        const double ip3li  = getMarkerValue("ip3li");
        const double ip3ui  = getMarkerValue("ip3ui");
        const double ip3mi  = getMarkerValue("ip3mi");

        const double ip5lo  = getMarkerValue("ip5lo");
        const double ip5uo  = getMarkerValue("ip5uo");
        const double ip5mo  = getMarkerValue("ip5mo");
        const double ip5li  = getMarkerValue("ip5li");
        const double ip5ui  = getMarkerValue("ip5ui");
        const double ip5mi  = getMarkerValue("ip5mi");

        const double ip7lo  = getMarkerValue("ip7lo");
        const double ip7uo  = getMarkerValue("ip7uo");
        const double ip7mo  = getMarkerValue("ip7mo");
        const double ip7li  = getMarkerValue("ip7li");
        const double ip7ui  = getMarkerValue("ip7ui");
        const double ip7mi  = getMarkerValue("ip7mi");

        const double ip9lo  = getMarkerValue("ip9lo");
        const double ip9uo  = getMarkerValue("ip9uo");
        const double ip9mo  = getMarkerValue("ip9mo");
        const double ip9li  = getMarkerValue("ip9li");
        const double ip9ui  = getMarkerValue("ip9ui");
        const double ip9mi  = getMarkerValue("ip9mi");

        // intermod major
        QVERIFY(isEqual(std::max(im3lo, im3uo), im3mo));
        QVERIFY(isEqual(std::max(im5lo, im5uo), im5mo));
        QVERIFY(isEqual(std::max(im7lo, im7uo), im7mo));
        QVERIFY(isEqual(std::max(im9lo, im9uo), im9mo));

        // intermod relative
        QVERIFY(isEqual(im3lor, lto - im3lo));
        QVERIFY(isEqual(im3uor, lto - im3uo));
        QVERIFY(isEqual(im3mor, lto - im3mo));
        QVERIFY(isEqual(std::min(im3uor, im3lor), im3mor));

        QVERIFY(isEqual(im5lor, lto - im5lo));
        QVERIFY(isEqual(im5uor, lto - im5uo));
        QVERIFY(isEqual(im5mor, lto - im5mo));
        QVERIFY(isEqual(std::min(im5uor, im5lor), im5mor));

        QVERIFY(isEqual(im7lor, lto - im7lo));
        QVERIFY(isEqual(im7uor, lto - im7uo));
        QVERIFY(isEqual(im7mor, lto - im7mo));
        QVERIFY(isEqual(std::min(im7uor, im7lor), im7mor));

        QVERIFY(isEqual(im9lor, lto - im9lo));
        QVERIFY(isEqual(im9uor, lto - im9uo));
        QVERIFY(isEqual(im9mor, lto - im9mo));
        QVERIFY(isEqual(std::min(im9uor, im9lor), im9mor));

        // output intercept
        QVERIFY(isEqual(ip3lo, lto + im3lor/2.0));
        QVERIFY(isEqual(ip3uo, lto + im3uor/2.0));
        QVERIFY(isEqual(ip3mo, lto + im3mor/2.0));
        QVERIFY(isEqual(std::min(ip3lo, ip3uo), ip3mo));

        QVERIFY(isEqual(ip5lo, lto + im5lor/4.0));
        QVERIFY(isEqual(ip5uo, lto + im5uor/4.0));
        QVERIFY(isEqual(ip5mo, lto + im5mor/4.0));
        QVERIFY(isEqual(std::min(ip5lo, ip5uo), ip5mo));

        QVERIFY(isEqual(ip7lo, lto + im7lor/6.0));
        QVERIFY(isEqual(ip7uo, lto + im7uor/6.0));
        QVERIFY(isEqual(ip7mo, lto + im7mor/6.0));
        QVERIFY(isEqual(std::min(ip7lo, ip7uo), ip7mo));

        QVERIFY(isEqual(ip9lo, lto + im9lor/8.0));
        QVERIFY(isEqual(ip9uo, lto + im9uor/8.0));
        QVERIFY(isEqual(ip9mo, lto + im9mor/8.0));
        QVERIFY(isEqual(std::min(ip9lo, ip9uo), ip9mo));

        // input intercept
        QVERIFY(isEqual(ip3li, lti + im3lor/2.0));
        QVERIFY(isEqual(ip3ui, lti + im3uor/2.0));
        QVERIFY(isEqual(ip3mi, lti + im3mor/2.0));
        QVERIFY(isEqual(std::min(ip3li, ip3ui), ip3mi));

        QVERIFY(isEqual(ip5li, lti + im5lor/4.0));
        QVERIFY(isEqual(ip5ui, lti + im5uor/4.0));
        QVERIFY(isEqual(ip5mi, lti + im5mor/4.0));
        QVERIFY(isEqual(std::min(ip5li, ip5ui), ip5mi));

        QVERIFY(isEqual(ip7li, lti + im7lor/6.0));
        QVERIFY(isEqual(ip7ui, lti + im7uor/6.0));
        QVERIFY(isEqual(ip7mi, lti + im7mor/6.0));
        QVERIFY(isEqual(std::min(ip7li, ip7ui), ip7mi));

        QVERIFY(isEqual(ip9li, lti + im9lor/8.0));
        QVERIFY(isEqual(ip9ui, lti + im9uor/8.0));
        QVERIFY(isEqual(ip9mi, lti + im9mor/8.0));
        QVERIFY(isEqual(std::min(ip9li, ip9ui), ip9mi));
    }
}

void ProcessTracesTest::debugPrint(QString header, QList<IntermodTrace> traces) {
    qDebug() << header.toUpper();
    for (int i = 0; i < traces.size(); i++) {
        qDebug() << "  " << traces[i].abbreviate();
    }
}

Traces ProcessTracesTest::allTraces() {
    // Original tones
    Traces traces;
    traces << IntermodTrace(TraceType::inputTone , TraceFeature::lower   );
    traces << IntermodTrace(TraceType::outputTone, TraceFeature::lower   );
    traces << IntermodTrace(TraceType::inputTone , TraceFeature::upper   );
    traces << IntermodTrace(TraceType::outputTone, TraceFeature::upper   );

    // Intermod
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

    // Relative
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

    // 3rd order intercept
    traces << IntermodTrace(TraceType::inputIntercept,  TraceFeature::lower, 3);
    traces << IntermodTrace(TraceType::inputIntercept,  TraceFeature::upper, 3);
    traces << IntermodTrace(TraceType::inputIntercept,  TraceFeature::major, 3);
    traces << IntermodTrace(TraceType::outputIntercept, TraceFeature::lower, 3);
    traces << IntermodTrace(TraceType::outputIntercept, TraceFeature::upper, 3);
    traces << IntermodTrace(TraceType::outputIntercept, TraceFeature::major, 3);

    // 5th order intercept
    traces << IntermodTrace(TraceType::inputIntercept,  TraceFeature::lower, 5);
    traces << IntermodTrace(TraceType::inputIntercept,  TraceFeature::upper, 5);
    traces << IntermodTrace(TraceType::inputIntercept,  TraceFeature::major, 5);
    traces << IntermodTrace(TraceType::outputIntercept, TraceFeature::lower, 5);
    traces << IntermodTrace(TraceType::outputIntercept, TraceFeature::upper, 5);
    traces << IntermodTrace(TraceType::outputIntercept, TraceFeature::major, 5);

    // 7th order intercept
    traces << IntermodTrace(TraceType::inputIntercept,  TraceFeature::lower, 7);
    traces << IntermodTrace(TraceType::inputIntercept,  TraceFeature::upper, 7);
    traces << IntermodTrace(TraceType::inputIntercept,  TraceFeature::major, 7);
    traces << IntermodTrace(TraceType::outputIntercept, TraceFeature::lower, 7);
    traces << IntermodTrace(TraceType::outputIntercept, TraceFeature::upper, 7);
    traces << IntermodTrace(TraceType::outputIntercept, TraceFeature::major, 7);

    // 9th order intercept
    traces << IntermodTrace(TraceType::inputIntercept,  TraceFeature::lower, 9);
    traces << IntermodTrace(TraceType::inputIntercept,  TraceFeature::upper, 9);
    traces << IntermodTrace(TraceType::inputIntercept,  TraceFeature::major, 9);
    traces << IntermodTrace(TraceType::outputIntercept, TraceFeature::lower, 9);
    traces << IntermodTrace(TraceType::outputIntercept, TraceFeature::upper, 9);
    traces << IntermodTrace(TraceType::outputIntercept, TraceFeature::major, 9);
    return traces;
}
double ProcessTracesTest::getMarkerValue(const QString prefix) {
    QString name;
    name = "%1_im_ch1";
    name = name.arg(prefix);
    return _vna->trace(name).marker(1).y();
}
bool ProcessTracesTest::isEqual(double left, double right) {
    const uint digits = 4;
    left  = round(left , digits);
    right = round(right, digits);
    if (!qFuzzyCompare(left, right)) {
        qDebug() << left << " != " << right;
        return false;
    }
    else {
        return true;
    }
}
