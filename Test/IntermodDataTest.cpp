#include "IntermodDataTest.h"


// Project
#include "IntermodData.h"


IntermodDataTest::IntermodDataTest(QObject *parent) :
    TestClass(parent)
{
    //
}

void IntermodDataTest::size() {
    uint spacingPoints = 101;
    uint centerPoints  = 201;
    IntermodData data(spacingPoints, centerPoints);

    // Tone
    QCOMPARE(data.lowerToneAtInput.size(),     spacingPoints);
    QCOMPARE(data.lowerToneAtInput[0].size(),  centerPoints);
    QCOMPARE(data.lowerToneAtOutput.size(),    spacingPoints);
    QCOMPARE(data.lowerToneAtOutput[0].size(), centerPoints);
    QCOMPARE(data.upperToneAtInput.size(),     spacingPoints);
    QCOMPARE(data.upperToneAtInput[0].size(),  centerPoints);
    QCOMPARE(data.upperToneAtOutput.size(),    spacingPoints);
    QCOMPARE(data.upperToneAtOutput[0].size(), centerPoints);

    // Intermod products
    QCOMPARE(data.intermod3Lower.size(),     spacingPoints);
    QCOMPARE(data.intermod3Lower[0].size(),  centerPoints);
    QCOMPARE(data.intermod3Upper.size(),     spacingPoints);
    QCOMPARE(data.intermod3Upper[0].size(),  centerPoints);
    QCOMPARE(data.intermod3Major.size(),     spacingPoints);
    QCOMPARE(data.intermod3Major[0].size(),  centerPoints);

    QCOMPARE(data.intermod5Lower.size(),     spacingPoints);
    QCOMPARE(data.intermod5Lower[0].size(),  centerPoints);
    QCOMPARE(data.intermod5Upper.size(),     spacingPoints);
    QCOMPARE(data.intermod5Upper[0].size(),  centerPoints);
    QCOMPARE(data.intermod5Major.size(),     spacingPoints);
    QCOMPARE(data.intermod5Major[0].size(),  centerPoints);

    QCOMPARE(data.intermod7Lower.size(),     spacingPoints);
    QCOMPARE(data.intermod7Lower[0].size(),  centerPoints);
    QCOMPARE(data.intermod7Upper.size(),     spacingPoints);
    QCOMPARE(data.intermod7Upper[0].size(),  centerPoints);
    QCOMPARE(data.intermod7Major.size(),     spacingPoints);
    QCOMPARE(data.intermod7Major[0].size(),  centerPoints);

    QCOMPARE(data.intermod9Lower.size(),     spacingPoints);
    QCOMPARE(data.intermod9Lower[0].size(),  centerPoints);
    QCOMPARE(data.intermod9Upper.size(),     spacingPoints);
    QCOMPARE(data.intermod9Upper[0].size(),  centerPoints);
    QCOMPARE(data.intermod9Major.size(),     spacingPoints);
    QCOMPARE(data.intermod9Major[0].size(),  centerPoints);

    // Intercept points
    QCOMPARE(data.intercept3Major.size(),    spacingPoints);
    QCOMPARE(data.intercept3Major[0].size(), centerPoints);
    QCOMPARE(data.intercept5Major.size(),    spacingPoints);
    QCOMPARE(data.intercept5Major[0].size(), centerPoints);
    QCOMPARE(data.intercept7Major.size(),    spacingPoints);
    QCOMPARE(data.intercept7Major[0].size(), centerPoints);
    QCOMPARE(data.intercept9Major.size(),    spacingPoints);
    QCOMPARE(data.intercept9Major[0].size(), centerPoints);
}
