#ifndef INTERMOD_MEASUREMENT_H
#define INTERMOD_MEASUREMENT_H


// Project
#include "IntermodData.h"
#include "IntermodSettings.h"
#include "Measurement.h"

// RsaToolbox
#include <General.h>
#include <Vna.h>

class IntermodError {
public:
    enum /*class*/ Code {
        LowerSourcePort,
        UpperSource,
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
    bool isError() const;
    Code code;
    QString message;
    void clear();
};

class IntermodMeasurement : public Measurement
{
public:
    IntermodMeasurement(RsaToolbox::Vna *vna,
                        uint referenceChannel,
                        const IntermodSettings &settings,
                        QObject *parent = 0);
    ~IntermodMeasurement();

    bool isValid() const;
    bool isValid(IntermodError &error) const;

    // ResultsType *results(); // Take?

public slots:
    virtual void run();

private:
    mutable RsaToolbox::Vna *_vna;
    uint                     _refChannel;
    IntermodSettings               _settings;

    QString _lti, _lto;
    QString _uti, _uto;
    QString _im3l, _im5l, _im7l, _im9l;
    QString _im3u, _im5u, _im7u, _im9u;
    QString _im3m, _im5m, _im7m, _im9m;
    QString _ip3m, _ip5m, _ip7m, _ip9m;
    void createTraces(uint channel, uint diagram);
    void deleteTraces();

    // Results
    IntermodData _data;
    void readData(uint i);
};

#endif // INTERMOD_MEASUREMENT_H
