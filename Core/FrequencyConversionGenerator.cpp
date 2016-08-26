#include "FrequencyConversionGenerator.h"


// RsaToolbox
#include <General.h>
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
    const double cf_Hz = _settings.centerFrequency_Hz ();
    const double td_Hz = _settings.stopToneDistance_Hz();
    return cf_Hz - (1.0/2.0) * td_Hz;
}
double FrequencyConversionGenerator::channelStopFrequency_Hz() const {
    const double cf_Hz = _settings.centerFrequency_Hz  ();
    const double td_Hz = _settings.startToneDistance_Hz();
    return cf_Hz - (1.0/2.0) * td_Hz;
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
    fc.setNumerator  ( 1.0*n);
    fc.setDenominator(1.0   );
    fc.setOffset     (double( 1 - n) * _settings.centerFrequency_Hz());
    return fc;
}
VnaArbitraryFrequency FrequencyConversionGenerator::upperOutput(uint n) const {
    VnaArbitraryFrequency fc;
    fc.setNumerator  (-1.0*n);
    fc.setDenominator(1.0   );
    fc.setOffset     (double( 1 + n) * _settings.centerFrequency_Hz());
    return fc;
}

double FrequencyConversionGenerator::minLowerFreq_Hz(uint n) const {
    const double cf_Hz = _settings.centerFrequency_Hz ();
    const double td_Hz = _settings.stopToneDistance_Hz();
    return cf_Hz - n/2.0 * td_Hz;
}
double FrequencyConversionGenerator::maxUpperFreq_Hz(uint n) const {
    const double cf_Hz = _settings.centerFrequency_Hz ();
    const double td_Hz = _settings.stopToneDistance_Hz();
    return cf_Hz + n/2.0 * td_Hz;
}
