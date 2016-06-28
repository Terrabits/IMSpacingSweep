#include "IntermodWidgetTest.h"


// Project
#include "IntermodWidget.h"

// RsaToolbox
using namespace RsaToolbox;

// Qt
#include <QApplication>
#include <QEventLoop>


IntermodWidgetTest::IntermodWidgetTest(ConnectionType type, const QString &address, QObject *parent) :
    VnaTestClass(type, address, parent)
{
    _applicationName = "Intermod Widget Test";
    _version         = "0.0";

    // Test results path
    _logDir.setPath(SOURCE_DIR);
    QString path = "IntermodWidgetTest";
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

    _logFilenames << "1 - Show.txt";
}

void IntermodWidgetTest::show() {
    QEventLoop loop;
    IntermodWidget widget(_vna.data());
    widget.show();
    loop.exec();
}
