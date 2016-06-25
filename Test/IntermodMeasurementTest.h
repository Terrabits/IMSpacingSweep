#ifndef INTERMODMEASUREMENTTEST_H
#define INTERMODMEASUREMENTTEST_H


// RsaToolbox
#include <GenericBus.h>
#include <VnaTestClass.h>

// Qt
#include <QObject>
#include <QString>


class IntermodMeasurementTest : public RsaToolbox::VnaTestClass
{
    Q_OBJECT
public:
    IntermodMeasurementTest(RsaToolbox::ConnectionType type, const QString &address, QObject *parent = 0);
    ~IntermodMeasurementTest();

private slots:
    void basic();
};


#endif // INTERMODMEASUREMENTTEST_H
