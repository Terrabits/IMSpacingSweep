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

void IntermodDataTest::empty() {
    IntermodData data;
    QVERIFY(data.isEmpty());
    QVERIFY(!data.centerPoints());
    QVERIFY(!data.distancePoints());
    QVERIFY(!data.isIM3());
    QVERIFY(!data.isIM5());
    QVERIFY(!data.isIM7());
    QVERIFY(!data.isIM9());
    QVERIFY(!data.isIP3());
    QVERIFY(!data.isIP5());
    QVERIFY(!data.isIP7());
    QVERIFY(!data.isIP9());
}

void IntermodDataTest::constructAll() {
    const uint distancePoints = 101;
    const uint centerPoints   = 201;

    IntermodSettings settings;
    settings.setToneDistancePoints(distancePoints);
    settings.setCenterFrequencyPoints(centerPoints);

    const uint order = 9;
    IntermodData data(settings, order);

    // Order
    QCOMPARE(data.maxOrder(), order);

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
    QVERIFY(data.isIM3());
    QCOMPARE(data.intermod3Lower.size(),     distancePoints);
    QCOMPARE(data.intermod3Lower[0].size(),  centerPoints);
    QCOMPARE(data.intermod3Upper.size(),     distancePoints);
    QCOMPARE(data.intermod3Upper[0].size(),  centerPoints);
    QCOMPARE(data.intermod3Major.size(),     distancePoints);
    QCOMPARE(data.intermod3Major[0].size(),  centerPoints);

    QVERIFY(data.isIM5());
    QCOMPARE(data.intermod5Lower.size(),     distancePoints);
    QCOMPARE(data.intermod5Lower[0].size(),  centerPoints);
    QCOMPARE(data.intermod5Upper.size(),     distancePoints);
    QCOMPARE(data.intermod5Upper[0].size(),  centerPoints);
    QCOMPARE(data.intermod5Major.size(),     distancePoints);
    QCOMPARE(data.intermod5Major[0].size(),  centerPoints);

    QVERIFY(data.isIM7());
    QCOMPARE(data.intermod7Lower.size(),     distancePoints);
    QCOMPARE(data.intermod7Lower[0].size(),  centerPoints);
    QCOMPARE(data.intermod7Upper.size(),     distancePoints);
    QCOMPARE(data.intermod7Upper[0].size(),  centerPoints);
    QCOMPARE(data.intermod7Major.size(),     distancePoints);
    QCOMPARE(data.intermod7Major[0].size(),  centerPoints);

    QVERIFY(data.isIM9());
    QCOMPARE(data.intermod9Lower.size(),     distancePoints);
    QCOMPARE(data.intermod9Lower[0].size(),  centerPoints);
    QCOMPARE(data.intermod9Upper.size(),     distancePoints);
    QCOMPARE(data.intermod9Upper[0].size(),  centerPoints);
    QCOMPARE(data.intermod9Major.size(),     distancePoints);
    QCOMPARE(data.intermod9Major[0].size(),  centerPoints);

    // Intercept points
    QVERIFY(data.isIP3());
    QCOMPARE(data.intercept3Major.size(),    distancePoints);
    QCOMPARE(data.intercept3Major[0].size(), centerPoints);

    QVERIFY(data.isIP5());
    QCOMPARE(data.intercept5Major.size(),    distancePoints);
    QCOMPARE(data.intercept5Major[0].size(), centerPoints);

    QVERIFY(data.isIP7());
    QCOMPARE(data.intercept7Major.size(),    distancePoints);
    QCOMPARE(data.intercept7Major[0].size(), centerPoints);

    QVERIFY(data.isIP9());
    QCOMPARE(data.intercept9Major.size(),    distancePoints);
    QCOMPARE(data.intercept9Major[0].size(), centerPoints);
}
void IntermodDataTest::onlyTo5thOrder() {
    const uint distancePoints = 101;
    const uint centerPoints   = 201;

    IntermodSettings settings;
    settings.setToneDistancePoints(distancePoints);
    settings.setCenterFrequencyPoints(centerPoints);

    const uint order = 5;
    IntermodData data(settings, order);

    // Order
    QCOMPARE(data.maxOrder(), order);

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
    QVERIFY(data.isIM3());
    QCOMPARE(data.intermod3Lower.size(),     distancePoints);
    QCOMPARE(data.intermod3Lower[0].size(),  centerPoints);
    QCOMPARE(data.intermod3Upper.size(),     distancePoints);
    QCOMPARE(data.intermod3Upper[0].size(),  centerPoints);
    QCOMPARE(data.intermod3Major.size(),     distancePoints);
    QCOMPARE(data.intermod3Major[0].size(),  centerPoints);

    QVERIFY(data.isIM5());
    QCOMPARE(data.intermod5Lower.size(),     distancePoints);
    QCOMPARE(data.intermod5Lower[0].size(),  centerPoints);
    QCOMPARE(data.intermod5Upper.size(),     distancePoints);
    QCOMPARE(data.intermod5Upper[0].size(),  centerPoints);
    QCOMPARE(data.intermod5Major.size(),     distancePoints);
    QCOMPARE(data.intermod5Major[0].size(),  centerPoints);

    QVERIFY(!data.isIM7());
    QVERIFY(!data.isIM9());

    // Intercept points
    QVERIFY(data.isIP3());
    QCOMPARE(data.intercept3Major.size(),    distancePoints);
    QCOMPARE(data.intercept3Major[0].size(), centerPoints);

    QVERIFY(data.isIP5());
    QCOMPARE(data.intercept5Major.size(),    distancePoints);
    QCOMPARE(data.intercept5Major[0].size(), centerPoints);

    QVERIFY(!data.isIP7());
    QVERIFY(!data.isIP9());
}
