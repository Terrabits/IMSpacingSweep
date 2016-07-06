#include "IntermodDataTest.h"


// Project
#include "IntermodData.h"


IntermodDataTest::IntermodDataTest(QObject *parent) :
    TestClass(parent)
{
    //
}
IntermodDataTest::~IntermodDataTest() {
    //
}

void IntermodDataTest::size() {
    const uint distancePoints = 101;
    const uint centerPoints   = 201;

    IntermodSettings settings;
    settings.setToneDistancePoints(distancePoints);
    settings.setCenterFrequencyPoints(centerPoints);

    IntermodData data(settings);

    // Tone
    QCOMPARE(data.lowerToneAtInput.size(),     distancePoints);
    QCOMPARE(data.lowerToneAtInput[0].size(),  centerPoints);
    QCOMPARE(data.lowerToneAtOutput.size(),    distancePoints);
    QCOMPARE(data.lowerToneAtOutput[0].size(), centerPoints);
    QCOMPARE(data.upperToneAtInput.size(),     distancePoints);
    QCOMPARE(data.upperToneAtInput[0].size(),  centerPoints);
    QCOMPARE(data.upperToneAtOutput.size(),    distancePoints);
    QCOMPARE(data.upperToneAtOutput[0].size(), centerPoints);

    // Intermod products
    QCOMPARE(data.intermod3Lower.size(),     distancePoints);
    QCOMPARE(data.intermod3Lower[0].size(),  centerPoints);
    QCOMPARE(data.intermod3Upper.size(),     distancePoints);
    QCOMPARE(data.intermod3Upper[0].size(),  centerPoints);
    QCOMPARE(data.intermod3Major.size(),     distancePoints);
    QCOMPARE(data.intermod3Major[0].size(),  centerPoints);

    QCOMPARE(data.intermod5Lower.size(),     distancePoints);
    QCOMPARE(data.intermod5Lower[0].size(),  centerPoints);
    QCOMPARE(data.intermod5Upper.size(),     distancePoints);
    QCOMPARE(data.intermod5Upper[0].size(),  centerPoints);
    QCOMPARE(data.intermod5Major.size(),     distancePoints);
    QCOMPARE(data.intermod5Major[0].size(),  centerPoints);

    QCOMPARE(data.intermod7Lower.size(),     distancePoints);
    QCOMPARE(data.intermod7Lower[0].size(),  centerPoints);
    QCOMPARE(data.intermod7Upper.size(),     distancePoints);
    QCOMPARE(data.intermod7Upper[0].size(),  centerPoints);
    QCOMPARE(data.intermod7Major.size(),     distancePoints);
    QCOMPARE(data.intermod7Major[0].size(),  centerPoints);

    QCOMPARE(data.intermod9Lower.size(),     distancePoints);
    QCOMPARE(data.intermod9Lower[0].size(),  centerPoints);
    QCOMPARE(data.intermod9Upper.size(),     distancePoints);
    QCOMPARE(data.intermod9Upper[0].size(),  centerPoints);
    QCOMPARE(data.intermod9Major.size(),     distancePoints);
    QCOMPARE(data.intermod9Major[0].size(),  centerPoints);

    // Intercept points
    QCOMPARE(data.intercept3Major.size(),    distancePoints);
    QCOMPARE(data.intercept3Major[0].size(), centerPoints);
    QCOMPARE(data.intercept5Major.size(),    distancePoints);
    QCOMPARE(data.intercept5Major[0].size(), centerPoints);
    QCOMPARE(data.intercept7Major.size(),    distancePoints);
    QCOMPARE(data.intercept7Major[0].size(), centerPoints);
    QCOMPARE(data.intercept9Major.size(),    distancePoints);
    QCOMPARE(data.intercept9Major[0].size(), centerPoints);
}
