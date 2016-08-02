#include "FrequencyConversion.h"

FrequencyConversion::FrequencyConversion() :
    _isGenerator(false),
    _numerator  (1.0),
    _denominator(1.0),
    _offset_Hz  (0.0)
{

}
FrequencyConversion::FrequencyConversion(double numerator, double denominator, double offset_Hz, bool isGenerator = false) :
    _isGenerator(isGenerator),
    _numerator  (numerator),
    _denominator(denominator),
    _offset_Hz  (offset_Hz)
{

}

FrequencyConversion::~FrequencyConversion()
{

}

bool   FrequencyConversion::isGenerator() const {
    return _isGenerator;
}
double FrequencyConversion::numerator  () const {
    return _numerator;
}
double FrequencyConversion::denominator() const {
    return _denominator;
}
double FrequencyConversion::offset_Hz  () const {
    return _offset_Hz;
}
void FrequencyConversion::setGenerator(bool isGenerator) {
    _isGenerator = isGenerator;
}

void FrequencyConversion::setNumerator(double value) {
    _numerator = value;
}
void FrequencyConversion::setDenominator(double value) {
    _denominator = value;
}
void FrequencyConversion::setOffset(double offset_Hz) {
    _offset_Hz = offset_Hz;
}

