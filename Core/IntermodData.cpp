#include "IntermodData.h"


// RsaToolbox
#include <General.h>
using namespace RsaToolbox;


// Functions
ComplexRowVector column(uint row, const ComplexMatrix2D &matrix) {
    const uint columns = matrix[0].size();
    ComplexRowVector result(columns);
    for (uint i = 0; i < columns; i++) {
        result[i] = matrix[row][i];
    }
    return result;
}

// Constructors
IntermodData::IntermodData() :
    _maxOrder(0)
{
    _settings.setToneDistancePoints(0);
    _settings.setCenterFrequencyPoints(0);
}
IntermodData::IntermodData(const IntermodSettings &settings, uint maxOrder)  :
    _settings(settings),
    _maxOrder(maxOrder)
{
    initialize();
}

IntermodData::~IntermodData() {
    //
}

bool IntermodData::isEmpty() const {
    if (centerPoints() == 0)
        return true;
    if (distancePoints() == 0)
        return true;

    // else
    return false;
}

// Settings
uint IntermodData::distancePoints() const {
    return _settings.toneDistancePoints();
}
uint IntermodData::centerPoints() const {
    return _settings.centerFrequencyPoints();
}
IntermodSettings IntermodData::settings() const {
    return _settings;
}
QRowVector IntermodData::centerFrequencies_Hz() const {
    const double start  = _settings.startCenterFrequency_Hz();
    const double stop   = _settings.stopCenterFrequency_Hz();
    const uint   points = _settings.centerFrequencyPoints();
    return linearSpacing(start, stop, points);
}
QRowVector IntermodData::distances_Hz() const {
    const double start  = _settings.startToneDistance_Hz();
    const double stop   = _settings.stopToneDistance_Hz();
    const uint   points = _settings.toneDistancePoints();
    return linearSpacing(start, stop, points);
}

uint IntermodData::maxOrder() const {
    return _maxOrder;
}
bool IntermodData::isIM3()    const {
    return _maxOrder >= 3;
}
bool IntermodData::isIM5()    const {
    return _maxOrder >= 5;
}
bool IntermodData::isIM7()    const {
    return _maxOrder >= 7;
}
bool IntermodData::isIM9()    const {
    return _maxOrder >= 9;
}
bool IntermodData::isIP3()    const {
    return isIM3();
}
bool IntermodData::isIP5()    const {
    return isIM5();
}
bool IntermodData::isIP7()    const {
    return isIM7();
}
bool IntermodData::isIP9()    const {
    return isIM9();
}

// Input frequencies
QRowVector IntermodData::lowerFrequencyAtCenter_Hz(double centerFrequency, SiPrefix prefix) const {
    return lowerFrequencyAtCenter_Hz(1, centerFrequency, prefix);
}
QRowVector IntermodData::lowerFrequencyAtDistance_Hz(double toneDistance, SiPrefix prefix) const {
    return lowerFrequencyAtDistance_Hz(1, toneDistance, prefix);
}
QRowVector IntermodData::upperFrequencyAtCenter_Hz(double centerFrequency, SiPrefix prefix) const {
    return upperFrequencyAtCenter_Hz(1, centerFrequency, prefix);
}
QRowVector IntermodData::upperFrequencyAtDistance_Hz(double toneDistance, SiPrefix prefix) const {
    return upperFrequencyAtDistance_Hz(1, toneDistance, prefix);
}

// Higher-order frequencies
QRowVector IntermodData::lowerFrequencyAtCenter_Hz(uint order, double centerFrequency, SiPrefix prefix) const {
    const double centerFrequency_Hz = centerFrequency * toDouble(prefix);
    const double start  = centerFrequency_Hz - 0.5*order * _settings.startToneDistance_Hz();
    const double stop   = centerFrequency_Hz - 0.5*order * _settings.stopToneDistance_Hz ();
    const uint   points = _settings.toneDistancePoints();
    return linearSpacing(start, stop, points);
}
QRowVector IntermodData::lowerFrequencyAtDistance_Hz(uint order, double toneDistance, SiPrefix prefix) const {
    const double toneDistance_Hz = toneDistance * toDouble(prefix);
    const double start  = _settings.startCenterFrequency_Hz() - 0.5*order * toneDistance_Hz;
    const double stop   = _settings.stopCenterFrequency_Hz () - 0.5*order * toneDistance_Hz;
    const uint   points = _settings.toneDistancePoints();
    return linearSpacing(start, stop, points);
}
QRowVector IntermodData::upperFrequencyAtCenter_Hz(uint order, double centerFrequency, SiPrefix prefix) const {
    const double centerFrequency_Hz = centerFrequency * toDouble(prefix);
    const double start  = centerFrequency_Hz + 0.5*order * _settings.startToneDistance_Hz();
    const double stop   = centerFrequency_Hz + 0.5*order * _settings.stopToneDistance_Hz ();
    const uint   points = _settings.toneDistancePoints();
    return linearSpacing(start, stop, points);
}
QRowVector IntermodData::upperFrequencyAtDistance_Hz(uint order, double toneDistance, SiPrefix prefix) const {
    const double toneDistance_Hz = toneDistance * toDouble(prefix);
    const double start  = _settings.startCenterFrequency_Hz() + 0.5*order * toneDistance_Hz;
    const double stop   = _settings.stopCenterFrequency_Hz () + 0.5*order * toneDistance_Hz;
    const uint   points = _settings.toneDistancePoints();
    return linearSpacing(start, stop, points);
}

void IntermodData::initialize() {
    ComplexDouble    emptyDouble(0,0);
    ComplexRowVector emptyVector(centerPoints(),   emptyDouble);
    ComplexMatrix2D  emptyMatrix(distancePoints(), emptyVector);

    switch(_maxOrder) {
    case 9:
        intermod9Lower    = emptyMatrix;
        intermod9Upper    = emptyMatrix;
        intermod9Major    = emptyMatrix;
        intercept9Major   = emptyMatrix;
        // And IM7
    case 7:
        intermod7Lower    = emptyMatrix;
        intermod7Upper    = emptyMatrix;
        intermod7Major    = emptyMatrix;
        intercept7Major   = emptyMatrix;
        // And IM5
    case 5:
        intermod5Lower    = emptyMatrix;
        intermod5Upper    = emptyMatrix;
        intermod5Major    = emptyMatrix;
        intercept5Major   = emptyMatrix;
        // And IM3
    case 3:
        intermod3Lower    = emptyMatrix;
        intermod3Upper    = emptyMatrix;
        intermod3Major    = emptyMatrix;
        intercept3Major   = emptyMatrix;
    default:
        // Always original tones
        lowerToneAtInput  = emptyMatrix;
        lowerToneAtOutput = emptyMatrix;
        upperToneAtInput  = emptyMatrix;
        upperToneAtOutput = emptyMatrix;
        break;
    }
}
