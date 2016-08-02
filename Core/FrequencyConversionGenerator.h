#ifndef FREQUENCYCONVERSIONGENERATOR_H
#define FREQUENCYCONVERSIONGENERATOR_H


// Project
#include "FrequencyConversion.h"
#include "IntermodSettings.h"


class FrequencyConversionGenerator
{
public:
    FrequencyConversionGenerator(const IntermodSettings &settings, double centerFrequency_Hz);
   ~FrequencyConversionGenerator();

    // channel base frequency (fb)
    double channelStartFrequency_Hz() const;
    double channelStopFrequency_Hz () const;

    // inputs
    FrequencyConversion lowerInput()  const;
    FrequencyConversion upperInput()  const;

    // Intermod (output)
    FrequencyConversion lowerOutput(uint n) const;
    FrequencyConversion upperOutput(uint n) const;

private:
    IntermodSettings _settings;
    double           _center_Hz;
};

#endif // FREQUENCYCONVERSIONGENERATOR_H
