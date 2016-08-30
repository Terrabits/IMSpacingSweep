#include "FrequencyConversionGenerator.h"


// RsaToolbox
#include <General.h>
using namespace RsaToolbox;

// Qt
#include <QDebug>

// stdlib
#include <algorithm>


FrequencyConversionGenerator::FrequencyConversionGenerator(const IntermodSettings &settings)
    : _settings(settings)
{

}
FrequencyConversionGenerator::~FrequencyConversionGenerator()
{

}

// channel
double FrequencyConversionGenerator::fbStart_Hz() const {
    const double cf_Hz = _settings.centerFrequency_Hz ();
    const double td_Hz = _settings.stopToneDistance_Hz();
    return cf_Hz - (1.0/2.0) * td_Hz;
}
double FrequencyConversionGenerator::fbStop_Hz() const {
    const double cf_Hz = _settings.centerFrequency_Hz  ();
    const double td_Hz = _settings.startToneDistance_Hz();
    return cf_Hz - (1.0/2.0) * td_Hz;
}
QRowVector FrequencyConversionGenerator::fb_Hz() const {
    QRowVector fdist = linearSpacing(fdStart(), fdStop(), points());
    QRowVector fb    = add(multiply(fdist, -0.5), fc_Hz());
    return sort(fb);
}

// input
VnaArbitraryFrequency FrequencyConversionGenerator::lowerInput() const {
    return lowerOutput(1);
}
QRowVector FrequencyConversionGenerator::lowerInputFreq_Hz() const {
    return fb_Hz();
}
VnaArbitraryFrequency FrequencyConversionGenerator::upperInput() const {
    VnaArbitraryFrequency fc = upperOutput(1);
    fc.setGeneratorPort(true);
    return fc;
}
QRowVector FrequencyConversionGenerator::upperInputFreq_Hz() const {
    double n      = -1.0;
    double offset = (1.0+1.0) * fc_Hz();
    QRowVector uif = add(multiply(fb_Hz(), n), offset);
    return sort(uif);
}

// intermod (output)
VnaArbitraryFrequency FrequencyConversionGenerator::lowerOutput(int n) const {
    VnaArbitraryFrequency fc;
    fc.setNumerator  ( 1.0*n);
    fc.setDenominator(1.0   );
    fc.setOffset     (( 1 - n) * fc_Hz());
    return fc;
}
QRowVector FrequencyConversionGenerator::lowerOutputFreq_Hz(int n) const {
    VnaArbitraryFrequency fc = lowerOutput(n);
    QRowVector f = add(multiply(fb_Hz(), fc.numerator()), fc.offset_Hz());
    return sort(f);
}
VnaArbitraryFrequency FrequencyConversionGenerator::upperOutput(int n) const {
    VnaArbitraryFrequency fc;
    fc.setNumerator  (-1.0*n);
    fc.setDenominator(1.0   );
    fc.setOffset     (( 1 + n) * _settings.centerFrequency_Hz());
    return fc;
}
QRowVector FrequencyConversionGenerator::upperOutputFreq_Hz(int n) const {
    VnaArbitraryFrequency fc = upperOutput(n);
    QRowVector f = add(multiply(fb_Hz(), fc.numerator()), fc.offset_Hz());
    return sort(f);
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

double FrequencyConversionGenerator::fc_Hz() const {
    return _settings.centerFrequency_Hz();
}
double FrequencyConversionGenerator::fdStart() const {
    return _settings.startToneDistance_Hz();
}
double FrequencyConversionGenerator::fdStop() const {
    return _settings.stopToneDistance_Hz();
}
uint FrequencyConversionGenerator::points() const {
    return _settings.points();
}
QRowVector FrequencyConversionGenerator::sort(QRowVector v) {
    std::sort(v.begin(), v.end());
    return v;
}
