#include "IntermodTraceTest.h"


// Project
#include "IntermodTrace.h"

// RsaToolbox
using namespace RsaToolbox;

// Qt
#include <QString>


IntermodTraceTest::IntermodTraceTest(QObject *parent) :
    TestClass(parent)
{
    //
}

IntermodTraceTest::~IntermodTraceTest()
{
    //
}

void IntermodTraceTest::trace_data() {
    QTest::addColumn<bool>   ("isValid");
    QTest::addColumn<QString>("y");
    QTest::addColumn<bool>   ("isYValid");
    QTest::addColumn<QString>("x");
    QTest::addColumn<bool>   ("isXValid");
    QTest::addColumn<QString>("at");
    QTest::addColumn<bool>   ("isAtValid");

    // Possible y values
    const QString lti  = "Lower Tone Input";
    const QString lto  = "Lower Tone Output";
    const QString uti  = "Upper Tone Input";
    const QString uto  = "Upper Tone Output";

    const QString im3l = "IM3 Lower";
    const QString im3u = "IM3 Upper";
    const QString im3m = "IM3 Major";

    const QString im5l = "IM5 Lower";
    const QString im5u = "IM5 Upper";
    const QString im5m = "IM5 Major";

    const QString im7l = "IM7 Lower";
    const QString im7u = "IM7 Upper";
    const QString im7m = "IM7 Major";

    const QString im9l = "IM9 Lower";
    const QString im9u = "IM9 Upper";
    const QString im9m = "IM9 Major";

    const QString ip3m = "IP3 Major";
    const QString ip5m = "IP5 Major";
    const QString ip7m = "IP7 Major";
    const QString ip9m = "IP9 Major";

    // Possible x/at values
    const QString cf   = "Center Frequency";
    const QString td   = "Tone Distance";

    //             Test            isValid  y       isYValid   x     isXValid   at    isAtValid
    QTest::newRow("Empty")      << false << ""   << false   << "" << false   << "" << false;
    QTest::newRow("Random")     << false << "ab" << false   <<"cd"<< false   <<"ef"<< false;

    // Original tones              isValid  y       isYValid   x     isXValid   at    isAtValid
    QTest::newRow("LTI-TD-CF")  << true  << lti  << true    << td << true    << cf << true;
    QTest::newRow("LTO-CF-TD")  << true  << lti  << true    << cf << true    << td << true;
    QTest::newRow("UTI-TD-TD")  << false << lti  << true    << td << true    << td << false;
    QTest::newRow("UTO-CF-CF")  << false << lti  << true    << cf << true    << cf << false;

    // Intermod                    isValid  y       isYValid   x     isXValid   at    isAtValid
    QTest::newRow("IM3L-TD-CF") << true  << im3l << true    << td << true    << cf << true;;
    QTest::newRow("IM5U-CF-TD") << true  << im5u << true    << cf << true    << td << true;
    QTest::newRow("IM7M-TD-TD") << false << im7m << true    << td << true    << td << false;
    QTest::newRow("IM9L-CF-CF") << false << im9l << true    << cf << true    << cf << false;

    // Intermod                    isValid  y       isYValid   x     isXValid   at    isAtValid
    QTest::newRow("IP3M-TD-CF") << true  << ip3m << true    << td << true    << cf << true;;
    QTest::newRow("IP5M-CF-TD") << true  << ip5m << true    << cf << true    << td << true;
    QTest::newRow("IP7M-TD-TD") << false << ip7m << true    << td << true    << td << false;
    QTest::newRow("IP9M-CF-CF") << false << ip9m << true    << cf << true    << cf << false;
}
void IntermodTraceTest::trace() {
    QFETCH(bool,    isValid);
    QFETCH(QString, y);
    QFETCH(bool,    isYValid);
    QFETCH(QString, x);
    QFETCH(bool,    isXValid);
    QFETCH(QString, at);
    QFETCH(bool,    isAtValid);

    IntermodTrace trace;
    trace.setY (y);
    trace.setX (x);
    trace.setAt(at);

    QCOMPARE(trace.y(),  y);
    QCOMPARE(trace.x(),  x);
    QCOMPARE(trace.at(), at);

    QCOMPARE(trace.isValid(),   isValid);
    QCOMPARE(trace.isYValid(),  isYValid);
    QCOMPARE(trace.isXValid(),  isXValid);
    QCOMPARE(trace.isAtValid(), isAtValid);
}

