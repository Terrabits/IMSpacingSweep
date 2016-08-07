#ifndef PROCESSTRACES_H
#define PROCESSTRACES_H


// RsaToolbox
#include <Vna.h>
#include <VnaArbitraryFrequency.h>

// Project
#include "FrequencyConversionGenerator.h"
#include "IntermodChannels.h"
#include "IntermodError.h"
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

    bool isReady(IntermodError &error);
    void run();

private:
    QList<IntermodTrace>         _traces;
    IntermodSettings             _settings;
    RsaToolbox::Vna             *_vna;
    IntermodChannels             _channels;
    FrequencyConversionGenerator _genFreq;
    uint                         _diagram;

    // isReady
    bool isFreqOutsideVna(const IntermodTrace &t) const;

    // Preprocess
    void preprocessTraces  ();
    bool hasDependency     (const IntermodTrace &t) const;
    void insertDependencies(const IntermodTrace &t);
    void sort              ();

    // Process
    void processTrace      (const IntermodTrace &t);

    // Processing by TraceType
    void processInputTrace    (const IntermodTrace &t);
    void processOutputTrace   (const IntermodTrace &t);
    void processIntermodTrace (const IntermodTrace &t);
    void processRelativeTrace (const IntermodTrace &t);
    void processInterceptTrace(const IntermodTrace &t);

    // Helpers
    QString channelName(const IntermodTrace &t);
    QString traceName  (const IntermodTrace &t);

    uint lowerPort () const;
    uint upperPort () const;
    uint outputPort() const;
    RsaToolbox::VnaArbitraryFrequency lowerAf() const;
    RsaToolbox::VnaArbitraryFrequency upperAf() const;
    RsaToolbox::VnaArbitraryFrequency outputAf(const IntermodTrace &t) const;





};

#endif // PROCESSTRACES_H
