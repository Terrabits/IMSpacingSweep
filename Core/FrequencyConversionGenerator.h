#ifndef FREQUENCYCONVERSIONGENERATOR_H
#define FREQUENCYCONVERSIONGENERATOR_H


// Project
#include "IntermodSettings.h"

// RsaToolbox
#include <VnaArbitraryFrequency.h>


class FrequencyConversionGenerator
{
public:
    FrequencyConversionGenerator(const IntermodSettings &settings);
   ~FrequencyConversionGenerator();

    // channel base frequency (fb)
    double fbStart_Hz() const;
    double fbStop_Hz () const;
    RsaToolbox::QRowVector fb_Hz() const;

    // inputs
    RsaToolbox::VnaArbitraryFrequency lowerInput()        const;
    RsaToolbox::QRowVector            lowerInputFreq_Hz() const;
    RsaToolbox::VnaArbitraryFrequency upperInput()        const;
    RsaToolbox::QRowVector            upperInputFreq_Hz() const;

    // Note: assumes order n odd

    // Intermod (output)
    RsaToolbox::VnaArbitraryFrequency lowerOutput(int n)  const;
    RsaToolbox::QRowVector            lowerOutputFreq_Hz(int n) const;
    RsaToolbox::VnaArbitraryFrequency upperOutput(int n)  const;
    RsaToolbox::QRowVector            upperOutputFreq_Hz(int n) const;

    double minLowerFreq_Hz(uint n) const;
    double maxUpperFreq_Hz(uint n) const;

private:
    IntermodSettings _settings;

    double fc_Hz     () const;
    double fdStart() const;
    double fdStop () const;
    uint   points () const;
    static RsaToolbox::QRowVector sort(RsaToolbox::QRowVector v);
};

#endif // FREQUENCYCONVERSIONGENERATOR_H
