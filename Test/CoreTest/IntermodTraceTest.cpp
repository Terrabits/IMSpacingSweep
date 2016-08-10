#include "IntermodTraceTest.h"


// Project
#include "IntermodTrace.h"

// RsaToolbox
using namespace RsaToolbox;

// Qt
#include <QDebug>
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
    QTest::addColumn<TraceFeature  >("feature" );
    QTest::addColumn<bool     >("hasOrder");
    QTest::addColumn<uint     >("order"   );

    // TEST NAME               TraceType                     Feature                hasOrder?   n
    QTest::newRow("uti"   ) << TraceType::inputTone       << TraceFeature::upper << false    << uint(0);
    QTest::newRow("lto"   ) << TraceType::outputTone      << TraceFeature::lower << false    << uint(0);
    QTest::newRow("im3m"  ) << TraceType::intermod        << TraceFeature::major << true     << uint(3);
    QTest::newRow("im5lr" ) << TraceType::relative        << TraceFeature::lower << true     << uint(5);
    QTest::newRow("ip7mo" ) << TraceType::outputIntercept << TraceFeature::major << true     << uint(7);
    QTest::newRow("ip7mi" ) << TraceType::inputIntercept  << TraceFeature::lower << true     << uint(9);
}
void IntermodTraceTest::accessors() {
    QFETCH(TraceType, type    );
    QFETCH(TraceFeature  , feature );
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
    QCOMPARE(t1.feature() , TraceFeature::lower );
    QCOMPARE(t1.hasOrder(), false         );

    IntermodTrace t2(TraceType::intermod, TraceFeature::major, /*order=*/ 3);
    QCOMPARE(t2.type()   , TraceType::intermod);
    QCOMPARE(t2.feature(), TraceFeature::major);
    QCOMPARE(t2.order()  , uint(3));

    IntermodTrace t3("5th Upper Output Intercept");
    QCOMPARE(t3.type()   , TraceType::outputIntercept);
    QCOMPARE(t3.feature(), TraceFeature::upper       );
    QCOMPARE(t3.order()  , uint(5));

    IntermodTrace t4("9th Lower Input Intercept");
    QCOMPARE(t4.type()   , TraceType::inputIntercept);
    QCOMPARE(t4.feature(), TraceFeature::lower      );
    QCOMPARE(t4.order()  , uint(9));

    IntermodTrace t5("Upper Input");
    QCOMPARE(t5.type()   , TraceType::inputTone);
    QCOMPARE(t5.feature(), TraceFeature::upper  );

    IntermodTrace t6("Lower Output");
    QCOMPARE(t6.type()   , TraceType::outputTone);
    QCOMPARE(t6.feature(), TraceFeature::lower  );
}

void IntermodTraceTest::display() {
    IntermodTrace t;
    t.setType(TraceType::relative);
    t.setFeature(TraceFeature::major);
    t.setOrder(9);
    QCOMPARE(t.display(), QString("9th Major Relative"));
}

void IntermodTraceTest::comparison() {
    IntermodTrace t1;
    t1.setType(TraceType::inputTone);
    t1.setFeature(TraceFeature::lower);

    IntermodTrace t2;
    t2.setType(TraceType::outputTone);
    t2.setFeature(TraceFeature::lower);

    QVERIFY(t1 != t2);
    QVERIFY(t1 < t2 );

    t1.setType(TraceType::outputTone);
    QVERIFY(  t1 == t2);
    QVERIFY(!(t1 <  t2));

    t1.setFeature(TraceFeature::upper);
    QVERIFY(  t1 != t2);
    QVERIFY(!(t1 <  t2));
}

void IntermodTraceTest::sort() {


    // 6th: 9th Major Intercept
    IntermodTrace t6;
    t6.setType   (TraceType::outputIntercept);
    t6.setFeature(TraceFeature::major);
    t6.setOrder  (9);

    IntermodTraces traces;
    traces << t6;

    // 5th: 5th Major Relative
    IntermodTrace t5;
    t5.setType   (TraceType::relative);
    t5.setFeature(TraceFeature::major);
    t5.setOrder  (5);
    traces << t5;

    // 4th: 5th Upper Relative
    IntermodTrace t4;
    t4.setType   (TraceType::relative);
    t4.setFeature(TraceFeature::upper);
    t4.setOrder  (5);
    traces << t4;

    // 3rd: 3rd Upper Relative
    IntermodTrace t3;
    t3.setType   (TraceType::relative);
    t3.setFeature(TraceFeature::upper);
    t3.setOrder  (3);
    traces << t3;

    // 2nd: Upper Output
    IntermodTrace t2;
    t2.setType   (TraceType::outputTone);
    t2.setFeature(TraceFeature::upper);
    traces << t2;

    // 1st: Lower Input
    IntermodTrace t1;
    t1.setType   (TraceType::inputTone);
    t1.setFeature(TraceFeature::lower);
    traces << t1;

    std::sort(traces.begin(), traces.end());
    QCOMPARE(traces[0], t1);
    QCOMPARE(traces[1], t2);
    QCOMPARE(traces[2], t3);
    QCOMPARE(traces[3], t4);
    QCOMPARE(traces[4], t5);
    QCOMPARE(traces[5], t6);
}
