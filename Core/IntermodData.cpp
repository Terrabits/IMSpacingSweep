#include "IntermodData.h"


// RsaToolbox
using namespace RsaToolbox;


IntermodData::IntermodData() :
    spacingPoints(0),
    centerPoints(0)
{
    //
}
IntermodData::IntermodData(uint spacingPoints, uint centerPoints)
{
    initialize(spacingPoints, centerPoints);
}

void IntermodData::initialize(uint spacingPoints, uint centerPoints) {
    this->spacingPoints = spacingPoints;
    this->centerPoints  = centerPoints;

    ComplexDouble emptyDouble(0,0);
    ComplexRowVector emptyVector(centerPoints, emptyDouble);
    ComplexMatrix2D emptyMatrix(spacingPoints, ComplexRowVector(centerPoints));

    // Tones
    lowerToneAtInput  = emptyMatrix;
    lowerToneAtOutput = emptyMatrix;
    upperToneAtInput  = emptyMatrix;
    upperToneAtOutput = emptyMatrix;

    // Intermod products
    intermod3Lower  = emptyMatrix;
    intermod3Upper  = emptyMatrix;
    intermod3Major  = emptyMatrix;

    intermod5Lower  = emptyMatrix;
    intermod5Upper  = emptyMatrix;
    intermod5Major  = emptyMatrix;

    intermod7Lower  = emptyMatrix;
    intermod7Upper  = emptyMatrix;
    intermod7Major  = emptyMatrix;

    intermod9Lower  = emptyMatrix;
    intermod9Upper  = emptyMatrix;
    intermod9Major  = emptyMatrix;

    // Intercept Points
    intercept3Major = emptyMatrix;
    intercept5Major = emptyMatrix;
    intercept7Major = emptyMatrix;
    intercept9Major = emptyMatrix;
}
