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
    QVERIFY(false);
}
