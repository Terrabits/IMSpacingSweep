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
    friend class ProcessTracesTest;

    ProcessTraces(const QList<IntermodTrace> &traces,
                  const IntermodSettings &settings,
                  RsaToolbox::Vna *vna,
                  uint baseChannel);
    ~ProcessTraces();

    bool isReady(IntermodError &error);
    uint baseChannel     () const;
    void setupCalibration();
    void run             ();

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
    //   Some traces depend on the existence
    //   of other traces. Need to add
    //   dependents to _traces.
    void preprocessTraces  ();
    void preprocessTrace   (const IntermodTrace &t);
    bool dependencyInTraces(const IntermodTrace &t) const;
    void sort              ();

    // Process
    void processTrace         (const IntermodTrace   &t);

    // Processing by TraceType
    void configureChannel     (RsaToolbox::VnaChannel c);
    void processInputTrace    (const IntermodTrace   &t);
    void processOutputTrace   (const IntermodTrace   &t);
    void processIntermodTrace (const IntermodTrace   &t);
    void processRelativeTrace (const IntermodTrace   &t);
    void processInterceptTrace(const IntermodTrace   &t);

    // Helpers
    QString traceName  (const IntermodTrace &t) const;
    uint createOrReuseDiagram();

    uint lowerPort () const;
    uint upperPort () const;
    uint outputPort() const;
    RsaToolbox::VnaArbitraryFrequency lowerAf () const;
    RsaToolbox::VnaArbitraryFrequency upperAf () const;
    RsaToolbox::VnaArbitraryFrequency outputAf(const IntermodTrace &t) const;
    QString math(const IntermodTrace &t) const;

    // Calibrate
    RsaToolbox::QRowVector fb_Hz () const;
    RsaToolbox::QRowVector upperFreq_Hz () const;
    RsaToolbox::QRowVector outputFreq_Hz(const IntermodTrace &t) const;
    RsaToolbox::QRowVector calFreq_Hz() const;
    static void includeOneOf(RsaToolbox::QRowVector &vector, double value);
    static void includeOneOf(RsaToolbox::QRowVector &vector, const RsaToolbox::QRowVector &values);
};

#endif // PROCESSTRACES_H
