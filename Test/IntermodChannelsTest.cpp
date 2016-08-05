#include "IntermodChannelsTest.h"


// Project
#include "IntermodChannels.h"
#include "IntermodTrace.h"

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
    const uint baseChannel = 1;
    IntermodChannels channels(_vna.data(), baseChannel);

    channels.collapse();
    QCOMPARE(_vna->numberOfChannels(), uint(1));
    QVERIFY (!_vna->isError());

    IntermodTrace t;
    t.setType   (TraceType::inputTone);
    t.setFeature(TraceFeature::upper);
    VnaChannel c;
    c = channels.create(t);
    QCOMPARE(c.name(), QString("uti_im_ch1"));
    QCOMPARE(_vna->numberOfChannels(), uint(1));
    QVERIFY (!_vna->isError());

    t.setType(TraceType::intercept);
    t.setFeature(TraceFeature::major);
    t.setOrder(7);
    c = channels.create(t);
    QCOMPARE(c.name(), QString("ip7mo_im_ch1"));
    QCOMPARE(_vna->numberOfChannels(), uint(2));
    QVERIFY (!_vna->isError());

    channels.collapse();
    QCOMPARE(_vna->numberOfChannels(), uint(1));
    QVERIFY (!_vna->isError());
}
