#ifndef PROCESSTRACESTEST_H
#define PROCESSTRACESTEST_H


// Project
#include "IntermodTrace.h"

// RsaToolbox
#include <VnaTestClass.h>

// Qt
#include <QString>


class ProcessTracesTest : public RsaToolbox::VnaTestClass
{
    Q_OBJECT
public:
    ProcessTracesTest(RsaToolbox::ConnectionType type, const QString &address, QObject *parent = 0);
    ~ProcessTracesTest();

private slots:
    virtual void initTestCase();

    void ready_data();
    void ready     ();

    void preprocess_data();
    void preprocess     ();

    void calFreq_data();
    void calFreq     ();

    void setCalFreq_data();
    void setCalFreq();

    void calibration_data();
    void calibration     ();

    void run_data();
    void run     ();

    void traceMath();

private:
    void debugPrint(QString header, IntermodTraces traces);

    static IntermodTraces allTraces();
    double getMarkerValue(const QString prefix);
    bool isEqual(double left, double right);

    double _vnaMin_Hz;
    double _vnaMax_Hz;

    void removeDuplicates(RsaToolbox::QRowVector &v);
    void sort(RsaToolbox::QRowVector &v);
    void compareRowVectors(RsaToolbox::QRowVector &actual, RsaToolbox::QRowVector &desired);

};

#endif // PROCESSTRACESTEST_H
