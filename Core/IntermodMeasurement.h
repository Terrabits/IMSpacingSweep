#ifndef INTERMOD_MEASUREMENT_H
#define INTERMOD_MEASUREMENT_H


// Project
#include "IntermodSettings.h"
#include "Measurement.h"

// RsaToolbox
#include <General.h>
#include <Vna.h>

class IntermodError {
public:
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

    IntermodError();
    ~IntermodError();
    Code code;
    QString message;

    bool isError() const;
};

class IntermodMeasurement : public Measurement
{
public:
    IntermodMeasurement(RsaToolbox::Vna *vna,
                        uint referenceChannel,
                        const IntermodSettings &settings,
                        QObject *parent = 0);
    ~IntermodMeasurement();

    bool isValid(IntermodError &error) const;

public slots:
    virtual void run();

private:
    mutable RsaToolbox::Vna *_vna;
    uint                     _refChannel;
    IntermodSettings               _settings;

    uint _channel;
};

#endif // INTERMOD_MEASUREMENT_H
