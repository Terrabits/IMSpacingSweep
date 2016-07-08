#ifndef INTERMOD_MEASUREMENT_H
#define INTERMOD_MEASUREMENT_H


// Project
#include "IntermodData.h"
#include "IntermodError.h"
#include "IntermodSettings.h"
#include "IntermodTrace.h"
#include "Measurement.h"

// RsaToolbox
#include <General.h>
#include <Vna.h>

// Qt
#include <QScopedPointer>




class IntermodMeasurement : public Measurement
{
public:
    IntermodMeasurement(RsaToolbox::Vna *vna,
                        uint referenceChannel,
                        const IntermodSettings &settings,
                        SharedIntermodTraces traces,
                        QObject *parent = 0);
    ~IntermodMeasurement();

    virtual bool isValid() const;
    bool isValid(IntermodError &error) const;

    IntermodData *takeResult();

public slots:
    virtual void run();

private:
    mutable RsaToolbox::Vna *_vna;
    uint                     _refChannel;
    IntermodSettings         _settings;
    SharedIntermodTraces     _traces;
    uint                     _maxOrder;
    uint maxOrder()     const;
    uint orderRequest() const;

    // Traces
    QString _lti, _lto;
    QString _uti, _uto;
    QString _im3l, _im5l, _im7l, _im9l;
    QString _im3u, _im5u, _im7u, _im9u;
    QString _im3m, _im5m, _im7m, _im9m;
    QString _ip3m, _ip5m, _ip7m, _ip9m;
    void createTraces(uint channel, uint diagram);
    void deleteTraces();

    // Results
    QScopedPointer<IntermodData> _data;
    void readData(uint i);
};

#endif // INTERMOD_MEASUREMENT_H
