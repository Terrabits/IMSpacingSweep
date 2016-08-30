#ifndef FREQUENCYCONVERSIONTEST_H
#define FREQUENCYCONVERSIONTEST_H


// Project
#include "FrequencyConversionGenerator.h"

// RsaToolbox
#include <VnaArbitraryFrequency.h>
#include <TestClass.h>

// Qt
#include <QObject>

////////////////////////////////////////
//  CASE 1:
//  center frequency = 1 GHz
//  tone distance    = [10 MHz ... 100 MHz]
//  points           = 10
//
//  | N | Side | Start     | Stop      |
//  |---|------|-----------|-----------|
//  | 1 | L    | 0.950 GHz | 0.995 GHz |
//  | 3 | L    | 0.850 GHz | 0.985 GHz |
//  | 5 | L    | 0.750 GHz | 0.975 GHz |
//  | 7 | L    | 0.650 GHz | 0.965 GHz |
//  | 9 | L    | 0.550 GHz | 0.955 GHz |
//  | 1 | U    | 1.050 GHz | 1.005 GHz |
//  | 3 | U    | 1.150 GHz | 1.015 GHz |
//  | 5 | U    | 1.250 GHz | 1.025 GHz |
//  | 7 | U    | 1.350 GHz | 1.035 GHz |
//  | 9 | U    | 1.450 GHz | 1.045 GHz |
//

/////////////////////////////////////////
//  CASE 2:
//  center frequency = 2 GHz
//  tone distance    = [1 MHz ... 10 MHz]
//  points           = 21
//
//  | N | Side | Start     | Stop       |
//  |---|------|-----------|------------|
//  | 1 | L    | 1.995 GHz | 1.9995 GHz |
//  | 3 | L    | 1.985 GHz | 1.9985 GHz |
//  | 5 | L    | 1.975 GHz | 1.9975 GHz |
//  | 7 | L    | 1.965 GHz | 1.9965 GHz |
//  | 9 | L    | 1.955 GHz | 1.9955 GHz |
//  | 1 | U    | 2.005 GHz | 2.0005 GHz |
//  | 3 | U    | 2.015 GHz | 2.0015 GHz |
//  | 5 | U    | 2.025 GHz | 2.0025 GHz |
//  | 7 | U    | 2.035 GHz | 2.0035 GHz |
//  | 9 | U    | 2.045 GHz | 2.0045 GHz |

class FrequencyConversionTest : public RsaToolbox::TestClass
{
    Q_OBJECT
public:
    explicit FrequencyConversionTest(QObject *parent = 0);
    ~FrequencyConversionTest();

private slots:
    void lti_data();
    void lti     ();

    void uti_data();
    void uti     ();

    void iml_data();
    void iml     ();

    void imu_data();
    void imu     ();
};

#endif // FREQUENCYCONVERSIONTEST_H
