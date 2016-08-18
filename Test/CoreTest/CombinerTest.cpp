#include "CombinerTest.h"


// Project
#include "CombinerEdit.h"
#include "IntermodCombiner.h"

// RsaToolbox
using namespace RsaToolbox;


CombinerTest::CombinerTest(QObject *parent) : TestClass(parent)
{

}

CombinerTest::~CombinerTest()
{

}

void CombinerTest::intermodCombiner() {
    IntermodCombiner ic;
    ic.setExternal();
    QVERIFY(ic.isExternal());
    QVERIFY(ic.at() == IntermodCombiner::At::External);

    ic.setPort(2);
    QVERIFY (ic.isPort());
    QVERIFY(ic.at() == IntermodCombiner::At::Port);
    QCOMPARE(ic.port(), uint(2));

    ic.setExternal();
    QVERIFY(ic.isExternal());
    QVERIFY(ic.at() == IntermodCombiner::At::External);
}
void CombinerTest::atConversion() {
    typedef IntermodCombiner::At At;
    typedef QString (*ToStringF)(At     );
    typedef At      (*ToAtF    )(QString);
    ToStringF toString = &IntermodCombiner::toString;
    ToAtF     toAt     = &IntermodCombiner::toAt;

    QString external = "External";
    QString port     = "Port";

    QCOMPARE(external,     toString(At::External));
    QCOMPARE(At::External, toAt("External"));

    QCOMPARE(port,     toString(At::Port));
    QCOMPARE(At::Port, toAt("Port"));
}

void CombinerTest::combinerEdit() {
    IntermodCombiner ic;
    ic.setExternal();

    CombinerEdit edit;
    edit.setCombiner(ic);
    QVERIFY(ic == edit.combiner());

    ic.setPort(2);
    edit.setCombiner(ic);
    QVERIFY(ic == edit.combiner());
}
