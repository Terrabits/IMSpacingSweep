#ifndef FREQUENCYCONVERSION_H
#define FREQUENCYCONVERSION_H


class FrequencyConversion
{
public:
    FrequencyConversion();
    FrequencyConversion(double numerator, double denominator, double offset_Hz, bool isGenerator);
    ~FrequencyConversion();

    bool   isGenerator() const;
    double numerator  () const;
    double denominator() const;
    double offset_Hz  () const;
    void   setGenerator  (bool isGenerator);
    void   setNumerator  (double value);
    void   setDenominator(double value);
    void   setOffset     (double offset_Hz);

private:
    bool   _isGenerator;
    double _numerator;
    double _denominator;
    double _offset_Hz;
};

#endif // FREQUENCYCONVERSION_H
