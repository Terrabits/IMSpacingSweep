#include "IntermodSettings.h"


// RsaToolbox
#include <General.h>
using namespace RsaToolbox;


IntermodSettings::IntermodSettings() :
    _lowerSourcePort(0),
    _receivingPort(0),
    _startCenterFreq_Hz(0),
    _stopCenterFreq_Hz(0),
    _centerFrequencyPoints(0),
    _startSpacing_Hz(0),
    _stopSpacing_Hz(0),
    _power_dBm(-1.0*DBL_MAX),
    _ifBw_Hz(10.0E3),
    _selectivity(VnaChannel::IfSelectivity::High)
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
void IntermodSettings::setStartSpacing(double frequency_Hz, SiPrefix prefix) {
    _startSpacing_Hz = frequency_Hz * toDouble(prefix);
}
void IntermodSettings::setStopSpacing(double frequency_Hz, SiPrefix prefix) {
    _stopSpacing_Hz  = frequency_Hz * toDouble(prefix);
}
void IntermodSettings::setSpacingPoints(uint points) {
    _spacingPoints   = points;
}

// Settings
double IntermodSettings::power_dBm() const {
    return _power_dBm;
}
double IntermodSettings::ifBw_Hz() const {
    return _ifBw_Hz;
}
VnaChannel::IfSelectivity IntermodSettings::selectivity() const {
    return _selectivity;
}
void IntermodSettings::setPower(double power_dBm) {
    _power_dBm = power_dBm;
}
void IntermodSettings::setIfBw(double frequency_Hz, SiPrefix prefix) {
    _ifBw_Hz = frequency_Hz * toDouble(prefix);
}
void IntermodSettings::setSelectivity(VnaChannel::IfSelectivity selectivity) {
    _selectivity = selectivity;
}


