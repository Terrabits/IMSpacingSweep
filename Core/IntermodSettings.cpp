#include "IntermodSettings.h"


// RsaToolbox
#include <General.h>
using namespace RsaToolbox;


IntermodSettings::IntermodSettings()
{
    //
}
IntermodSettings::~IntermodSettings()
{
    //
}

// Ports
uint IntermodSettings::lowerSourcePort() const {
    return _lowerSourcePort;
}
VnaIntermod::ToneSource IntermodSettings::upperSource() const {
    return _upperSource;
}
uint IntermodSettings::receivingPort() const {
    return _receivingPort;
}
void IntermodSettings::setLowerSourcePort(uint port) {
    _lowerSourcePort = port;
}
void IntermodSettings::setUpperSource(VnaIntermod::ToneSource source) {
    _upperSource = source;
}
void IntermodSettings::setReceivingPort(uint port) {
    _receivingPort = port;
}

// Center Frequency
double IntermodSettings::startCenterFrequency_Hz() const {
    return _startCenterFreq_Hz;
}
double IntermodSettings::stopCenterFrequency_Hz() const  {
    return _stopCenterFreq_Hz;
}
uint IntermodSettings::centerFrequencyPoints() const {
    return _centerFrequencyPoints;
}
void IntermodSettings::setStartCenterFrequency(double frequency_Hz, SiPrefix prefix) {
    _startCenterFreq_Hz = frequency_Hz * toDouble(prefix);
}
void IntermodSettings::setStopCenterFrequency(double frequency_Hz, SiPrefix prefix) {
    _stopCenterFreq_Hz = frequency_Hz * toDouble(prefix);
}
void IntermodSettings::setCenterFrequencyPoints(uint points) {
    _centerFrequencyPoints = points;
}

// Tone spacing (distance)
double IntermodSettings::startSpacing_Hz() const {
    return _startSpacing_Hz;
}
double IntermodSettings::stopSpacing_Hz() const {
    return _stopSpacing_Hz;
}
uint IntermodSettings::spacingPoints() const {
    return _spacingPoints;
}
