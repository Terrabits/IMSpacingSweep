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
    QTest::addColumn<QString>("name");
    QTest::addColumn<bool>   ("isNameValid");
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

    //             Test            isValid  name      isNameValid  y       isYValid   x     isXValid   at    isAtValid
    QTest::newRow("Empty")      << false << ""     << false     << ""   << false   << "" << false   << "" << false;
    QTest::newRow("Random")     << false << "_y"   << true      << "ab" << false   <<"cd"<< false   <<"ef"<< false;
    QTest::newRow("SpaceInName")<< false << "a b"  << false     << ""   << false   << "" << false   << "" << false;
    QTest::newRow("Punctuation")<< false << "a.b"  << false     << ""   << false   << "" << false   << "" << false;

    // Original tones              isValid  name      isNameValid  y       isYValid   x     isXValid   at    isAtValid
    QTest::newRow("LTI-TD-CF")  << true  << "LTITD"<< true      << lti  << true    << td << true    << cf << true;
    QTest::newRow("LTO-CF-TD")  << true  << "LTOCF"<< true      << lti  << true    << cf << true    << td << true;
    QTest::newRow("UTI-TD-TD")  << false << "UTITD"<< true      << lti  << true    << td << true    << td << false;
    QTest::newRow("UTO-CF-CF")  << false << "UTOCF"<< true      << lti  << true    << cf << true    << cf << false;

    // Intermod                    isValid  name      isNameValid  y       isYValid   x     isXValid   at    isAtValid
    QTest::newRow("IM3L-TD-CF") << true  << "IM3LD"<< true      << im3l << true    << td << true    << cf << true;;
    QTest::newRow("IM5U-CF-TD") << true  << "IM5UC"<< true      << im5u << true    << cf << true    << td << true;
    QTest::newRow("IM7M-TD-TD") << false << "IM7MD"<< true      << im7m << true    << td << true    << td << false;
    QTest::newRow("IM9L-CF-CF") << false << "IM9LC"<< true      << im9l << true    << cf << true    << cf << false;

    // Intermod                    isValid  name      isNameValid  y       isYValid   x     isXValid   at    isAtValid
    QTest::newRow("IP3M-TD-CF") << true  << "IP3MD"<< true      << ip3m << true    << td << true    << cf << true;;
    QTest::newRow("IP5M-CF-TD") << true  << "IP5MC"<< true      << ip5m << true    << cf << true    << td << true;
    QTest::newRow("IP7M-TD-TD") << false << "IP7MD"<< true      << ip7m << true    << td << true    << td << false;
    QTest::newRow("IP9M-CF-CF") << false << "IP9MC"<< true      << ip9m << true    << cf << true    << cf << false;
}
void IntermodTraceTest::trace() {
    QFETCH(bool,    isValid);
    QFETCH(QString, name);
    QFETCH(bool,    isNameValid);
    QFETCH(QString, y);
    QFETCH(bool,    isYValid);
    QFETCH(QString, x);
    QFETCH(bool,    isXValid);
    QFETCH(QString, at);
    QFETCH(bool,    isAtValid);

    IntermodTrace trace;
    trace.setName(name);
    trace.setY (y);
    trace.setX (x);
    trace.setAt(at);

    QCOMPARE(trace.name(), name);
    QCOMPARE(trace.y(),    y);
    QCOMPARE(trace.x(),    x);
    QCOMPARE(trace.at(),   at);

    QCOMPARE(trace.isValid(),     isValid);
    QCOMPARE(trace.isNameValid(), isNameValid);
    QCOMPARE(trace.isYValid(),    isYValid);
    QCOMPARE(trace.isXValid(),    isXValid);
    QCOMPARE(trace.isAtValid(),   isAtValid);
}

