#include "FrequencyConversionTest.h"


// Project
#include "IntermodSettings.h"

// RsaToolbox
using namespace RsaToolbox;


FrequencyConversionTest::FrequencyConversionTest(QObject *parent) : TestClass(parent)
{

}

FrequencyConversionTest::~FrequencyConversionTest()
{

}

// tests
void FrequencyConversionTest::basic() {
    //  center frequency = 1 GHz
    //  tone distance    = [10 MHz ... 100 MHz]
    //
    //  | N | Side | Start      | Stop    |
    //  |---|------|-----------|----------|
    //  | 1 | L    | 0.995 GHz | 0.95 GHz |
    //  | 3 | L    | 0.985 GHz | 0.85 GHz |
    //  | 5 | L    | 0.975 GHz | 0.75 GHz |
    //  | 7 | L    | 0.965 GHz | 0.65 GHz |
    //  | 9 | L    | 0.955 GHz | 0.55 GHz |
    //  | 1 | U    | 1.005 GHz | 1.05 GHz |
    //  | 3 | U    | 1.015 GHz | 1.15 GHz |
    //  | 5 | U    | 1.025 GHz | 1.25 GHz |
    //  | 7 | U    | 1.035 GHz | 1.35 GHz |
    //  | 9 | U    | 1.045 GHz | 1.45 GHz |
    //

    // distance
    IntermodSettings s;
    s.setStartToneDistance( 10, SiPrefix::Mega);
    s.setStopToneDistance (100, SiPrefix::Mega);
    s.setPoints(10);

    // center
    const double centerFreq_Hz = 1.0e9;
    s.setCenterFrequency(centerFreq_Hz);

    // Channel settings
    double fbStart_Hz = 0.995e9;
    double fbStop_Hz  = 0.950e9;
    FrequencyConversionGenerator g(s);
    QCOMPARE(g.channelStartFrequency_Hz(), fbStart_Hz);
    QCOMPARE(g.channelStopFrequency_Hz (), fbStop_Hz );

    // lower input
    //   = fb
    VnaArbitraryFrequency fc = g.lowerInput();
    QVERIFY (!fc.isGeneratorPort());
    QCOMPARE(fc.numerator(),   1.0);
    QCOMPARE(fc.denominator(), 1.0);
    QCOMPARE(fc.offset_Hz(),   0.0);
    QCOMPARE(calculateLowerInput_Hz(g, fbStart_Hz), fbStart_Hz);
    QCOMPARE(calculateLowerInput_Hz(g, fbStop_Hz ), fbStop_Hz );

    // upper input
    double start_Hz = 1.005e9;
    double stop_Hz  = 1.050e9;
    QVERIFY (g.upperInput().isGeneratorPort());
    QCOMPARE(calculateUpperInput_Hz(g, fbStart_Hz), start_Hz);
    QCOMPARE(calculateUpperInput_Hz(g, fbStop_Hz ), stop_Hz );

    // lower output
    uint n = 1;
    start_Hz = 0.995e9;
    stop_Hz  = 0.950e9;
    QVERIFY (!g.lowerOutput(n).isGeneratorPort());
    QCOMPARE(calculateLowerOutput_Hz(g, n, fbStart_Hz), start_Hz);
    QCOMPARE(calculateLowerOutput_Hz(g, n, fbStop_Hz ), stop_Hz );

    n = 3;
    start_Hz = 0.985e9;
    stop_Hz  = 0.850e9;
    QVERIFY (!g.lowerOutput(n).isGeneratorPort());
    QCOMPARE(calculateLowerOutput_Hz(g, n, fbStart_Hz), start_Hz);
    QCOMPARE(calculateLowerOutput_Hz(g, n, fbStop_Hz ), stop_Hz );

    n = 5;
    start_Hz = 0.975e9;
    stop_Hz  = 0.750e9;
    QVERIFY (!g.lowerOutput(n).isGeneratorPort());
    QCOMPARE(calculateLowerOutput_Hz(g, n, fbStart_Hz), start_Hz);
    QCOMPARE(calculateLowerOutput_Hz(g, n, fbStop_Hz ), stop_Hz );

    n = 7;
    start_Hz = 0.965e9;
    stop_Hz  = 0.650e9;
    QVERIFY (!g.lowerOutput(n).isGeneratorPort());
    QCOMPARE(calculateLowerOutput_Hz(g, n, fbStart_Hz), start_Hz);
    QCOMPARE(calculateLowerOutput_Hz(g, n, fbStop_Hz ), stop_Hz );

    n = 9;
    start_Hz = 0.955e9;
    stop_Hz  = 0.550e9;
    QVERIFY (!g.lowerOutput(n).isGeneratorPort());
    QCOMPARE(calculateLowerOutput_Hz(g, n, fbStart_Hz), start_Hz);
    QCOMPARE(calculateLowerOutput_Hz(g, n, fbStop_Hz ), stop_Hz );

    // upper output
    n = 1;
    start_Hz = 1.005e9;
    stop_Hz  = 1.050e9;
    QVERIFY (!g.upperOutput(n).isGeneratorPort());
    QCOMPARE(calculateUpperOutput_Hz(g, n, fbStart_Hz), start_Hz);
    QCOMPARE(calculateUpperOutput_Hz(g, n, fbStop_Hz ), stop_Hz );

    n = 3;
    start_Hz = 1.015e9;
    stop_Hz  = 1.150e9;
    QVERIFY (!g.upperOutput(n).isGeneratorPort());
    QCOMPARE(calculateUpperOutput_Hz(g, n, fbStart_Hz), start_Hz);
    QCOMPARE(calculateUpperOutput_Hz(g, n, fbStop_Hz ), stop_Hz );

    n = 5;
    start_Hz = 1.025e9;
    stop_Hz  = 1.250e9;
    QVERIFY (!g.upperOutput(n).isGeneratorPort());
    QCOMPARE(calculateUpperOutput_Hz(g, n, fbStart_Hz), start_Hz);
    QCOMPARE(calculateUpperOutput_Hz(g, n, fbStop_Hz ), stop_Hz );

    n = 7;
    start_Hz = 1.035e9;
    stop_Hz  = 1.350e9;
    QVERIFY (!g.upperOutput(n).isGeneratorPort());
    QCOMPARE(calculateUpperOutput_Hz(g, n, fbStart_Hz), start_Hz);
    QCOMPARE(calculateUpperOutput_Hz(g, n, fbStop_Hz ), stop_Hz );

    n = 9;
    start_Hz = 1.045e9;
    stop_Hz  = 1.450e9;
    QVERIFY (!g.upperOutput(n).isGeneratorPort());
    QCOMPARE(calculateUpperOutput_Hz(g, n, fbStart_Hz), start_Hz);
    QCOMPARE(calculateUpperOutput_Hz(g, n, fbStop_Hz ), stop_Hz );
}
void FrequencyConversionTest::limits() {
    //  center frequency = 1 GHz
    //  tone distance    = [10 MHz ... 100 MHz]
    //
    //  | N | Side | Start      | Stop    |
    //  |---|------|-----------|----------|
    //  | 1 | L    | 0.995 GHz | 0.95 GHz |
    //  | 3 | L    | 0.985 GHz | 0.85 GHz |
    //  | 5 | L    | 0.975 GHz | 0.75 GHz |
    //  | 7 | L    | 0.965 GHz | 0.65 GHz |
    //  | 9 | L    | 0.955 GHz | 0.55 GHz |
    //  | 1 | U    | 1.005 GHz | 1.05 GHz |
    //  | 3 | U    | 1.015 GHz | 1.15 GHz |
    //  | 5 | U    | 1.025 GHz | 1.25 GHz |
    //  | 7 | U    | 1.035 GHz | 1.35 GHz |
    //  | 9 | U    | 1.045 GHz | 1.45 GHz |
    //
    IntermodSettings settings;
    settings.setCenterFrequency  (1,   SiPrefix::Giga);
    settings.setStartToneDistance(10,  SiPrefix::Mega);
    settings.setStopToneDistance (100, SiPrefix::Mega);
    settings.setPoints(10);

    FrequencyConversionGenerator gen(settings);
    QCOMPARE(gen.minLowerFreq_Hz(1), 0.95e9);
    QCOMPARE(gen.minLowerFreq_Hz(3), 0.85e9);
    QCOMPARE(gen.minLowerFreq_Hz(5), 0.75e9);
    QCOMPARE(gen.minLowerFreq_Hz(7), 0.65e9);
    QCOMPARE(gen.minLowerFreq_Hz(9), 0.55e9);
    QCOMPARE(gen.maxUpperFreq_Hz(1), 1.05e9);
    QCOMPARE(gen.maxUpperFreq_Hz(3), 1.15e9);
    QCOMPARE(gen.maxUpperFreq_Hz(5), 1.25e9);
    QCOMPARE(gen.maxUpperFreq_Hz(7), 1.35e9);
    QCOMPARE(gen.maxUpperFreq_Hz(9), 1.45e9);
}

// private
double FrequencyConversionTest::calculateConversion_Hz(const VnaArbitraryFrequency &c, double fb_Hz) {
    return (c.numerator() / c.denominator()) * fb_Hz + c.offset_Hz();
}
double FrequencyConversionTest::calculateLowerInput_Hz(const FrequencyConversionGenerator &g, double fb_Hz) {
    VnaArbitraryFrequency fc = g.lowerInput();
    return calculateConversion_Hz(fc, fb_Hz);
}
double FrequencyConversionTest::calculateUpperInput_Hz(const FrequencyConversionGenerator &g, double fb_Hz) {
    VnaArbitraryFrequency fc = g.upperInput();
    return calculateConversion_Hz(fc, fb_Hz);
}
double FrequencyConversionTest::calculateLowerOutput_Hz(const FrequencyConversionGenerator &g, uint n, double fb_Hz) {
    VnaArbitraryFrequency fc = g.lowerOutput(n);
    return calculateConversion_Hz(fc, fb_Hz);
}
double FrequencyConversionTest::calculateUpperOutput_Hz(const FrequencyConversionGenerator &g, uint n, double fb_Hz) {
    VnaArbitraryFrequency fc = g.upperOutput(n);
    return calculateConversion_Hz(fc, fb_Hz);
}
