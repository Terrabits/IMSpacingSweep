#include "CombinerTest.h"


// Project
#include "CombinerEdit.h"
#include "IntermodCombiner.h"

// RsaToolbox
using namespace RsaToolbox;

// Qt
#include <QByteArray>
#include <QDataStream>


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
void CombinerTest::save() {
    QByteArray bytes;
    QDataStream stream(&bytes, QIODevice::ReadWrite);

    IntermodCombiner ic1;
    ic1.setExternal();
    stream << ic1;

    stream.device()->seek(0);

    IntermodCombiner ic2;
    stream >> ic2;
    QVERIFY(ic1.isExternal());
    QVERIFY(ic2.isExternal());

    stream.device()->seek(0);
    bytes.clear();

    ic2.setPort(3);
    stream << ic2;

    stream.device()->seek(0);
    stream >> ic1;
    QVERIFY(ic1.isPort());
    QCOMPARE(ic1.port(), uint(3));
    QVERIFY(ic1 == ic2);
}

void CombinerTest::combinerEdit() {
    IntermodCombiner ic;
    ic.setExternal();

    CombinerEdit edit;
    edit.enablePort();

    edit.setValue(ic);
    QVERIFY(ic == edit.value());

    ic.setPort(2);
    edit.setValue(ic);
    QVERIFY(ic == edit.value());
}
