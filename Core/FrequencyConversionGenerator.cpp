#include "FrequencyConversionGenerator.h"


FrequencyConversionGenerator::FrequencyConversionGenerator(const IntermodSettings &settings, double centerFrequency_Hz) :
    _settings(settings),
    _center_Hz(centerFrequency_Hz)
{

}
FrequencyConversionGenerator::~FrequencyConversionGenerator()
{

}

// channel
double FrequencyConversionGenerator::channelStartFrequency_Hz() const {
    return _center_Hz - (1.0/2.0) * _settings.startToneDistance_Hz();
}
double FrequencyConversionGenerator::channelStopFrequency_Hz() const {
    return _center_Hz - (1.0/2.0) * _settings.stopToneDistance_Hz();
}

// input
FrequencyConversion FrequencyConversionGenerator::lowerInput() const {
    return lowerOutput(1);
}
FrequencyConversion FrequencyConversionGenerator::upperInput() const {
    FrequencyConversion fc = upperOutput(1);
    fc.setGenerator(true);
    return fc;
}

// intermod (output)
FrequencyConversion FrequencyConversionGenerator::lowerOutput(uint n) const {
    FrequencyConversion fc;
    if (n == 1)
        return fc;

    const uint np =  (n + 1)/2;
    fc.setNumerator  (np );
    fc.setDenominator(1.0);
    fc.setOffset     (( 1.0 - np) * _center_Hz);
    return fc;
}
FrequencyConversion FrequencyConversionGenerator::upperOutput(uint n) const {
    FrequencyConversion fc;
    const uint np = (n + 1)/2;
    fc.setNumerator  (-1.0*np);
    fc.setDenominator(1.0    );
    fc.setOffset     (( 1.0 + np) * _center_Hz);
    return fc;
}
