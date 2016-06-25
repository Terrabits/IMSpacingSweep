#ifndef INTERMODDATA_H
#define INTERMODDATA_H


// RsaToolbox
#include <Definitions.h>


class IntermodData
{
public:
    IntermodData();
    IntermodData(uint spacingPoints, uint centerPoints);

    uint spacingPoints;
    uint centerPoints;

    // Tones
    RsaToolbox::ComplexMatrix2D lowerToneAtInput;
    RsaToolbox::ComplexMatrix2D lowerToneAtOutput;
    RsaToolbox::ComplexMatrix2D upperToneAtInput;
    RsaToolbox::ComplexMatrix2D upperToneAtOutput;

    // Intermod products
    RsaToolbox::ComplexMatrix2D intermod3Lower;
    RsaToolbox::ComplexMatrix2D intermod3Upper;
    RsaToolbox::ComplexMatrix2D intermod3Major;

    RsaToolbox::ComplexMatrix2D intermod5Lower;
    RsaToolbox::ComplexMatrix2D intermod5Upper;
    RsaToolbox::ComplexMatrix2D intermod5Major;

    RsaToolbox::ComplexMatrix2D intermod7Lower;
    RsaToolbox::ComplexMatrix2D intermod7Upper;
    RsaToolbox::ComplexMatrix2D intermod7Major;

    RsaToolbox::ComplexMatrix2D intermod9Lower;
    RsaToolbox::ComplexMatrix2D intermod9Upper;
    RsaToolbox::ComplexMatrix2D intermod9Major;

    // Intercept Points
    RsaToolbox::ComplexMatrix2D intercept3Major;
    RsaToolbox::ComplexMatrix2D intercept5Major;
    RsaToolbox::ComplexMatrix2D intercept7Major;
    RsaToolbox::ComplexMatrix2D intercept9Major;

private:
    void initialize(uint spacingPoints, uint centerPoints);
};

#endif // INTERMODDATA_H
