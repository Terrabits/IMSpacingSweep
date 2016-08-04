#ifndef FREQUENCYCONVERSIONTEST_H
#define FREQUENCYCONVERSIONTEST_H


// Project
#include "FrequencyConversionGenerator.h"

// RsaToolbox
#include <VnaArbitraryFrequency.h>
#include <TestClass.h>

// Qt
#include <QObject>


class FrequencyConversionTest : public RsaToolbox::TestClass
{
    Q_OBJECT
public:
    explicit FrequencyConversionTest(QObject *parent = 0);
    ~FrequencyConversionTest();

private slots:
    void basic();

private:
    static double calculateConversion_Hz (const RsaToolbox::VnaArbitraryFrequency &c,         double fb_Hz);
    static double calculateLowerInput_Hz (const FrequencyConversionGenerator      &g,         double fb_Hz);
    static double calculateUpperInput_Hz (const FrequencyConversionGenerator      &g,         double fb_Hz);
    static double calculateLowerOutput_Hz(const FrequencyConversionGenerator      &g, uint n, double fb_Hz);
    static double calculateUpperOutput_Hz(const FrequencyConversionGenerator      &g, uint n, double fb_Hz);
};

#endif // FREQUENCYCONVERSIONTEST_H
