#ifndef PROCESSTRACES_H
#define PROCESSTRACES_H


// RsaToolbox
#include <Vna.h>
#include <VnaArbitraryFrequency.h>

// Project
#include "FrequencyConversionGenerator.h"
#include "IntermodChannels.h"
#include "IntermodSettings.h"
#include "IntermodTrace.h"

// Qt
#include <QList>
#include <Qt>


class ProcessTraces
{
public:
    ProcessTraces(const QList<IntermodTraces> &traces,
                  const IntermodSettings &settings,
                  RsaToolbox::Vna *vna,
                  uint baseChannel);
    ~ProcessTraces();

private:
    QList<IntermodTrace>         _traces;
    IntermodSettings             _settings;
    RsaToolbox::Vna             *_vna;
    IntermodChannels             _channels;
    FrequencyConversionGenerator _genFreq;
    uint                         _diagram;

    void preprocessTraces();
    void processTrace    (const IntermodTrace &t);

    QString channelName(const IntermodTrace &t);
    QString traceName  (const IntermodTrace &t);

    uint lowerPort () const;
    uint upperPort () const;
    uint outputPort() const;
    RsaToolbox::VnaArbitraryFrequency lowerAf() const;
    RsaToolbox::VnaArbitraryFrequency upperAf() const;
    RsaToolbox::VnaArbitraryFrequency outputAf(const IntermodTrace &t) const;

    // Processing by TraceType
    void processInputTrace    (const IntermodTrace &t);
    void processOutputTrace   (const IntermodTrace &t);
    void processIntermodTrace (const IntermodTrace &t);
    void processRelativeTrace (const IntermodTrace &t);
    void processInterceptTrace(const IntermodTrace &t);



};

#endif // PROCESSTRACES_H
