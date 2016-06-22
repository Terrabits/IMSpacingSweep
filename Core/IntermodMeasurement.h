#ifndef INTERMOD_MEASUREMENT_H
#define INTERMOD_MEASUREMENT_H


// Project
#include "IMSettings.h"
#include "Measurement.h"

// RsaToolbox
#include <General.h>
#include <Vna.h>

class IntermodError {
    enum /*class*/ Code {
        LowerSourcePort,
        UpperSourcePort,
        ReceivingPort,
        StartCenterFreq,
        StopCenterFreq,
        CenterFreqPoints,
        StartSpacing,
        StopSpacing,
        SpacingPoints,
        Power,
        IfBw,
        Selectivity,
        None
    };

    Code code;
    QString message;
};

class IntermodMeasurement : public Measurement
{
public:
    IntermodMeasurement(RsaToolbox::Vna *vna, uint referenceChannel, const IMSettings &settings);

    bool isValid(IntermodError &error) const;

public slots:
    virtual void run();

private:
    mutable RsaToolbox::Vna *_vna;
    uint                     _refChannel;
    IMSettings               _settings;

    uint _channel;
};

#endif // INTERMOD_MEASUREMENT_H
