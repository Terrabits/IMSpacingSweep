#ifndef INTERMODMEASUREMENTTEST_H
#define INTERMODMEASUREMENTTEST_H


// RsaToolbox
#include <VnaTestClass.h>


class IntermodMeasurementTest : public RsaToolbox::VnaTestClass
{
public:
    IntermodMeasurementTest(RsaToolbox::ConnectionType type, const QString &address, QObject *parent = 0);
    ~IntermodMeasurementTest();

private slots:
    void basic();
};

#endif // INTERMODMEASUREMENTTEST_H
