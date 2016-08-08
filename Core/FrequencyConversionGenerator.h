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
    double channelStartFrequency_Hz() const;
    double channelStopFrequency_Hz () const;

    // inputs
    RsaToolbox::VnaArbitraryFrequency lowerInput()  const;
    RsaToolbox::VnaArbitraryFrequency upperInput()  const;

    // Note: assumes order n odd

    // Intermod (output)
    RsaToolbox::VnaArbitraryFrequency lowerOutput(uint n) const;
    RsaToolbox::VnaArbitraryFrequency upperOutput(uint n) const;

    double minLowerFreq_Hz  (uint n) const;
    double maxUpperFreq_Hz  (uint n) const;

private:
    IntermodSettings _settings;
};

#endif // FREQUENCYCONVERSIONGENERATOR_H
