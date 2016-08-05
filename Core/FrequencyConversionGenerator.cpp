#include "FrequencyConversionGenerator.h"


// RsaToolbox
using namespace RsaToolbox;

FrequencyConversionGenerator::FrequencyConversionGenerator(const IntermodSettings &settings)
    : _settings(settings)
{

}
FrequencyConversionGenerator::~FrequencyConversionGenerator()
{

}

// channel
double FrequencyConversionGenerator::channelStartFrequency_Hz() const {
    return _settings.centerFrequency_Hz() - (1.0/2.0) * _settings.startToneDistance_Hz();
}
double FrequencyConversionGenerator::channelStopFrequency_Hz() const {
    return _settings.centerFrequency_Hz() - (1.0/2.0) * _settings.stopToneDistance_Hz();
}

// input
VnaArbitraryFrequency FrequencyConversionGenerator::lowerInput() const {
    return lowerOutput(1);
}
VnaArbitraryFrequency FrequencyConversionGenerator::upperInput() const {
    VnaArbitraryFrequency fc = upperOutput(1);
    fc.setGeneratorPort(true);
    return fc;
}

// intermod (output)
VnaArbitraryFrequency FrequencyConversionGenerator::lowerOutput(uint n) const {
    VnaArbitraryFrequency fc;
    if (n == 1)
        return fc;

    const uint np =  (n + 1)/2;
    fc.setNumerator  (np );
    fc.setDenominator(1.0);
    fc.setOffset     (( 1.0 - np) * _settings.centerFrequency_Hz());
    return fc;
}
VnaArbitraryFrequency FrequencyConversionGenerator::upperOutput(uint n) const {
    VnaArbitraryFrequency fc;
    const uint np = (n + 1)/2;
    fc.setNumerator  (-1.0*np);
    fc.setDenominator(1.0    );
    fc.setOffset     (( 1.0 + np) * _settings.centerFrequency_Hz());
    return fc;
}

double FrequencyConversionGenerator::minLowerFreq_Hz(uint n) {
    return 0;
}
double FrequencyConversionGenerator::maxUpperFreq_Hz(uint n) {
    return 1.0E12;
}
