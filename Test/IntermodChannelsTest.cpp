#include "IntermodChannelsTest.h"


// Project
#include "IntermodChannels.h"

// RsaToolbox
#include <Test.h>
#include <VnaChannel.h>
using namespace RsaToolbox;


IntermodChannelsTest::IntermodChannelsTest(ConnectionType type, const QString &address, QObject *parent) :
    VnaTestClass(type, address, parent)
{
    _applicationName = "Intermod Channels Test";
    _version         = "0.0";

    // Test results path
    _logDir.setPath(SOURCE_DIR);
    QString path = "IntermodChannelsTest";
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

IntermodChannelsTest::~IntermodChannelsTest()
{

}

void IntermodChannelsTest::basic() {
    // Ch1, Trc1, diagram 1
    // points: 201

    // Ch2, Trc2
    _vna->createChannel();
    _vna->createTrace("Trc2", 2);
    _vna->trace("Trc2").setDiagram(1);

    // Ch3
    _vna->createChannel(); // ch3
    _vna->createTrace("Trc3", 3);
    _vna->trace("Trc3").setDiagram(1);

    const uint points        = 123;
    const uint baseChannel   = 2;
    _vna->channel(baseChannel).linearSweep().setPoints(points);

    IntermodChannels channels(_vna.data(), baseChannel);

    int size = 1;
    QCOMPARE(channels.all().size(), size);
    QCOMPARE(_vna->channel(baseChannel).name(), QString("intermod1"));
    QCOMPARE(_vna->channel(baseChannel).linearSweep().points(), points);

    VnaChannel c;
    c = channels.create();
    size++;
    QCOMPARE(c.name()                , QString("intermod2"));
    QCOMPARE(channels.all().size()   , size);
    QCOMPARE(c.linearSweep().points(), points);

    c = channels.create();
    size++;
    QCOMPARE(c.name()                , QString("intermod3"));
    QCOMPARE(channels.all().size()   , size);
    QCOMPARE(c.linearSweep().points(), points);

    c = channels.create();
    size++;
    QCOMPARE(c.name()                , QString("intermod4"));
    QCOMPARE(channels.all().size()   , size);
    QCOMPARE(c.linearSweep().points(), points);

    // remove all but base
    channels.collapse();
    QCOMPARE(channels.all().size(),        1);
    QCOMPARE(channels.all().first(),  uint(2));
}
