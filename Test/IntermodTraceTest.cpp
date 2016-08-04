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
    QTest::addColumn<bool>   ("isAtValid");

    // Possible y values
    const QString lti  = "Lower In";
    const QString lto  = "Lower Out";
    const QString uti  = "Upper In";
    const QString uto  = "Upper Out";

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

    //             Test            isValid  name      isNameValid  y       isYValid
    QTest::newRow("Empty")      << false << ""     << false     << ""   << false;
    QTest::newRow("Random")     << false << "_y"   << true      << "ab" << false;
    QTest::newRow("SpaceInName")<< false << "a b"  << false     << ""   << false;
    QTest::newRow("Punctuation")<< false << "a.b"  << false     << ""   << false;

    // Original tones              isValid  name      isNameValid  y       isYValid
    QTest::newRow("LTI-TD-CF")  << true  << "LTITD"<< true      << lti  << true;
    QTest::newRow("LTO-CF-TD")  << true  << "LTOCF"<< true      << lti  << true;
    QTest::newRow("UTI-TD-TD")  << false << "UTITD"<< true      << lti  << true;
    QTest::newRow("UTO-CF-CF")  << false << "UTOCF"<< true      << lti  << true;

    // Intermod                    isValid  name      isNameValid  y       isYValid
    QTest::newRow("IM3L-TD-CF") << true  << "IM3LD"<< true      << im3l << true;
    QTest::newRow("IM5U-CF-TD") << true  << "IM5UC"<< true      << im5u << true;
    QTest::newRow("IM7M-TD-TD") << false << "IM7MD"<< true      << im7m << true;
    QTest::newRow("IM9L-CF-CF") << false << "IM9LC"<< true      << im9l << true;

    // Intermod                    isValid  name      isNameValid  y       isYValid
    QTest::newRow("IP3M-TD-CF") << true  << "IP3MD"<< true      << ip3m << true;
    QTest::newRow("IP5M-CF-TD") << true  << "IP5MC"<< true      << ip5m << true;
    QTest::newRow("IP7M-TD-TD") << false << "IP7MD"<< true      << ip7m << true;
    QTest::newRow("IP9M-CF-CF") << false << "IP9MC"<< true      << ip9m << true;
}
void IntermodTraceTest::trace() {
    QFETCH(bool,    isValid);
    QFETCH(QString, name);
    QFETCH(bool,    isNameValid);
    QFETCH(QString, y);
    QFETCH(bool,    isYValid);

    IntermodTrace trace;
    trace.setName(name);
    trace.setY (y);

    QCOMPARE(trace.name(), name);
    QCOMPARE(trace.y(),    y);

    QCOMPARE(trace.isValid(),     isValid);
    QCOMPARE(trace.isNameValid(), isNameValid);
    QCOMPARE(trace.isYValid(),    isYValid);
}

