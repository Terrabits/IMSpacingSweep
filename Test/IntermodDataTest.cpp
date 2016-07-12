#include "IntermodDataTest.h"


// Project
#include "IntermodData.h"

// RsaToolbox
using namespace RsaToolbox;


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
    testMatrix(data.lowerToneAtInput,  distancePoints, centerPoints);
    testMatrix(data.upperToneAtInput,  distancePoints, centerPoints);
    testMatrix(data.lowerToneAtOutput, distancePoints, centerPoints);
    testMatrix(data.upperToneAtOutput, distancePoints, centerPoints);

    // Intermod products
    QVERIFY(data.isIM3());
    testMatrix(data.intermod3Lower,  distancePoints, centerPoints);
    testMatrix(data.intermod3Upper,  distancePoints, centerPoints);
    testMatrix(data.intermod3Major,  distancePoints, centerPoints);

    QVERIFY(data.isIM5());
    testMatrix(data.intermod5Lower,  distancePoints, centerPoints);
    testMatrix(data.intermod5Upper,  distancePoints, centerPoints);
    testMatrix(data.intermod5Major,  distancePoints, centerPoints);

    QVERIFY(data.isIM7());
    testMatrix(data.intermod7Lower,  distancePoints, centerPoints);
    testMatrix(data.intermod7Upper,  distancePoints, centerPoints);
    testMatrix(data.intermod7Major,  distancePoints, centerPoints);

    QVERIFY(data.isIM9());
    testMatrix(data.intermod9Lower,  distancePoints, centerPoints);
    testMatrix(data.intermod9Upper,  distancePoints, centerPoints);
    testMatrix(data.intermod9Major,  distancePoints, centerPoints);

    // Intercept points
    QVERIFY(data.isIP3());
    QVERIFY(data.isIP5());
    QVERIFY(data.isIP7());
    QVERIFY(data.isIP9());
    testMatrix(data.intercept3Major,  distancePoints, centerPoints);
    testMatrix(data.intercept5Major,  distancePoints, centerPoints);
    testMatrix(data.intercept7Major,  distancePoints, centerPoints);
    testMatrix(data.intercept9Major,  distancePoints, centerPoints);
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
    testMatrix(data.lowerToneAtInput,  distancePoints, centerPoints);
    testMatrix(data.upperToneAtInput,  distancePoints, centerPoints);
    testMatrix(data.lowerToneAtOutput, distancePoints, centerPoints);
    testMatrix(data.upperToneAtOutput, distancePoints, centerPoints);

    // Intermod products
    QVERIFY(data.isIM3());
    testMatrix(data.intermod3Lower,  distancePoints, centerPoints);
    testMatrix(data.intermod3Upper,  distancePoints, centerPoints);
    testMatrix(data.intermod3Major,  distancePoints, centerPoints);

    QVERIFY(data.isIM5());
    testMatrix(data.intermod5Lower,  distancePoints, centerPoints);
    testMatrix(data.intermod5Upper,  distancePoints, centerPoints);
    testMatrix(data.intermod5Major,  distancePoints, centerPoints);

    QVERIFY(!data.isIM7());
    QVERIFY(!data.isIM9());

    // Intercept points
    QVERIFY(data.isIP3());
    QVERIFY(data.isIP5());
    QVERIFY(!data.isIP7());
    QVERIFY(!data.isIP9());
    testMatrix(data.intercept3Major,  distancePoints, centerPoints);
    testMatrix(data.intercept5Major,  distancePoints, centerPoints);
}

void IntermodDataTest::columnFunction() {
    const uint rows    = 101;
    const uint columns =  10;

    const ComplexDouble zero(0,0);
    const ComplexRowVector row(columns, zero);
    ComplexMatrix2D matrix(rows, row);

    QCOMPARE(column(matrix, 0).size(), rows);
    QCOMPARE(column(matrix, 1).size(), rows);
    QCOMPARE(column(matrix, 9).size(), rows);
}

void IntermodDataTest::testMatrix(const ComplexMatrix2D &matrix, uint rows, uint columns) {
    QCOMPARE(matrix.size(), rows);
    for (uint i = 0; i < rows; i++) {
        QCOMPARE(matrix[i].size(), columns);
    }
}
