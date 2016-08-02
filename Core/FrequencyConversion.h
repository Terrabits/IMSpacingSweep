#ifndef FREQUENCYCONVERSION_H
#define FREQUENCYCONVERSION_H


// Project
#include "IntermodSettings.h"


class FrequencyConversion
{
public:
    FrequencyConversion(const IntermodSettings &settings);
    ~FrequencyConversion();

    uint points() const;
    void lowerTone(double &start, double &stop);
    void lowerTone(uint N, double &numerator, double &denominator, double &offset);
    void upperTone(uint N, double &numerator, double &denominator, double &offset);

private:
    IntermodSettings _settings;
};

#endif // FREQUENCYCONVERSION_H
