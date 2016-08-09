

// Project
#include "IntermodError.h"
#include "IntermodWidget.h"

// RsaToolbox
#include <Vna.h>
using namespace RsaToolbox;

// Qt
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Vna vna(ConnectionType::VisaTcpSocketConnection, "127.0.0.1::5025");
    IntermodWidget w(&vna);
    w.show();
    int result = a.exec();

    vna.preset();

    IntermodError e;
    qDebug() << "is input? " << w.isInput(e);
    qDebug() << "is error? " << e.isError();
    qDebug() << "message:  " << e.message;
    return result;
}
