#include "IntermodTraceTest.h"


// Project
#include "IntermodTrace.h"

// RsaToolbox
using namespace RsaToolbox;

// Qt
#include <QString>

// std lib
#include <algorithm>


IntermodTraceTest::IntermodTraceTest(QObject *parent) :
    TestClass(parent)
{
    //
}

IntermodTraceTest::~IntermodTraceTest()
{
    //
}

void IntermodTraceTest::accessors_data() {
    QTest::addColumn<TraceType>("type"    );
    QTest::addColumn<Feature  >("feature" );
    QTest::addColumn<bool     >("hasOrder");
    QTest::addColumn<uint     >("order"   );

    // TEST NAME              TraceType                Feature           hasOrder?   n
    QTest::newRow("uti"  ) << TraceType::inputTone  << Feature::upper << false    << uint(0);
    QTest::newRow("lto"  ) << TraceType::outputTone << Feature::lower << false    << uint(0);
    QTest::newRow("im3m" ) << TraceType::intermod   << Feature::major << true     << uint(3);
    QTest::newRow("im5lr") << TraceType::relative   << Feature::lower << true     << uint(5);
    QTest::newRow("ip7m" ) << TraceType::intercept  << Feature::major << true     << uint(7);
}
void IntermodTraceTest::accessors() {
    QFETCH(TraceType, type    );
    QFETCH(Feature  , feature );
    QFETCH(bool     , hasOrder);
    QFETCH(uint     , order   );

    IntermodTrace t;
    t.setType   (type   );
    t.setFeature(feature);
    t.setOrder  (order  );
    QCOMPARE(t.type    (), type    );
    QCOMPARE(t.feature (), feature );
    QCOMPARE(t.hasOrder(), hasOrder);
    if (t.hasOrder())
        QCOMPARE(t.order(), order);
}

void IntermodTraceTest::constructors() {
    IntermodTrace t1;
    QCOMPARE(t1.type()    , TraceType::inputTone);
    QCOMPARE(t1.feature() , Feature::lower);
    QCOMPARE(t1.hasOrder(), false         );

    IntermodTrace t2(TraceType::intermod, Feature::major, /*order=*/ 3);
    QCOMPARE(t2.type()   , TraceType::intermod);
    QCOMPARE(t2.feature(), Feature::major     );
    QCOMPARE(t2.order()  , uint(3));

    IntermodTrace t3("5th Upper Intercept");
    QCOMPARE(t3.type()   , TraceType::intercept);
    QCOMPARE(t3.feature(), Feature::upper      );
    QCOMPARE(t3.order()  , uint(5));
}

void IntermodTraceTest::display() {
    IntermodTrace t;
    t.setType(TraceType::relative);
    t.setFeature(Feature::major);
    t.setOrder(9);
    QCOMPARE(t.display(), QString("9th Major Relative"));
}

void IntermodTraceTest::comparison() {
    IntermodTrace t1;
    t1.setType(TraceType::inputTone);
    t1.setFeature(Feature::lower);

    IntermodTrace t2;
    t2.setType(TraceType::outputTone);
    t2.setFeature(Feature::lower);

    QVERIFY(t1 != t2);
    QVERIFY(t1 < t2 );

    t1.setType(TraceType::outputTone);
    QVERIFY(  t1 == t2);
    QVERIFY(!(t1 <  t2));

    t1.setFeature(Feature::upper);
    QVERIFY(  t1 != t2);
    QVERIFY(!(t1 <  t2));
}

void IntermodTraceTest::sort() {


    // 6th: 9th Major Intercept
    IntermodTrace t6;
    t6.setType   (TraceType::intercept);
    t6.setFeature(Feature::major);
    t6.setOrder  (9);

    QList<IntermodTrace> traces;
    traces << t6;

    // 5th: 5th Major Relative
    IntermodTrace t5;
    t5.setType   (TraceType::relative);
    t5.setFeature(Feature::major);
    t5.setOrder  (5);
    traces << t5;

    // 4th: 5th Upper Relative
    IntermodTrace t4;
    t4.setType   (TraceType::relative);
    t4.setFeature(Feature::upper);
    t4.setOrder  (5);
    traces << t4;

    // 3rd: 3rd Upper Relative
    IntermodTrace t3;
    t3.setType   (TraceType::relative);
    t3.setFeature(Feature::upper);
    t3.setOrder  (3);
    traces << t3;

    // 2nd: Upper Output
    IntermodTrace t2;
    t2.setType   (TraceType::outputTone);
    t2.setFeature(Feature::upper);
    traces << t2;

    // 1st: Lower Input
    IntermodTrace t1;
    t1.setType   (TraceType::inputTone);
    t1.setFeature(Feature::lower);
    traces << t1;

    std::sort(traces.begin(), traces.end());
    QCOMPARE(traces[0], t1);
    QCOMPARE(traces[1], t2);
    QCOMPARE(traces[2], t3);
    QCOMPARE(traces[3], t4);
    QCOMPARE(traces[4], t5);
    QCOMPARE(traces[5], t6);
}
