#ifndef INTERMODDATA_H
#define INTERMODDATA_H


// Project
#include "IntermodSettings.h"

// RsaToolbox
#include <Definitions.h>


// Functions
RsaToolbox::ComplexRowVector column(const RsaToolbox::ComplexMatrix2D &matrix, uint index);

// Data
struct IntermodData
{
    IntermodData();
    IntermodData(const IntermodSettings &settings, uint maxOrder);
   ~IntermodData();

    bool isEmpty() const;
//    void clear();

    // Settings
    uint distancePoints() const;
    uint centerPoints()   const;
    IntermodSettings       settings()             const;
    RsaToolbox::QRowVector centerFrequencies_Hz() const;
    RsaToolbox::QRowVector distances_Hz()         const;

    // Input frequencies
    RsaToolbox::QRowVector lowerFrequencyAtCenter_Hz  (double centerFrequency, RsaToolbox::SiPrefix prefix = RsaToolbox::SiPrefix::None) const;
    RsaToolbox::QRowVector lowerFrequencyAtDistance_Hz(double toneDistance,    RsaToolbox::SiPrefix prefix = RsaToolbox::SiPrefix::None) const;
    RsaToolbox::QRowVector upperFrequencyAtCenter_Hz  (double centerFrequency, RsaToolbox::SiPrefix prefix = RsaToolbox::SiPrefix::None) const;
    RsaToolbox::QRowVector upperFrequencyAtDistance_Hz(double toneDistance,    RsaToolbox::SiPrefix prefix = RsaToolbox::SiPrefix::None) const;

    // Higher-order frequencies
    RsaToolbox::QRowVector lowerFrequencyAtCenter_Hz  (uint order, double centerFrequency, RsaToolbox::SiPrefix prefix = RsaToolbox::SiPrefix::None) const;
    RsaToolbox::QRowVector lowerFrequencyAtDistance_Hz(uint order, double toneDistance,    RsaToolbox::SiPrefix prefix = RsaToolbox::SiPrefix::None) const;
    RsaToolbox::QRowVector upperFrequencyAtCenter_Hz  (uint order, double centerFrequency, RsaToolbox::SiPrefix prefix = RsaToolbox::SiPrefix::None) const;
    RsaToolbox::QRowVector upperFrequencyAtDistance_Hz(uint order, double toneDistance,    RsaToolbox::SiPrefix prefix = RsaToolbox::SiPrefix::None) const;

    // Matrices:
    // Y[distance][center] = a + j*b

    // Tones
    RsaToolbox::ComplexMatrix2D lowerToneAtInput;
    RsaToolbox::ComplexMatrix2D lowerToneAtOutput;
    RsaToolbox::ComplexMatrix2D upperToneAtInput;
    RsaToolbox::ComplexMatrix2D upperToneAtOutput;

    uint maxOrder() const;

    // Intermod products
    bool isIM3()    const;
    RsaToolbox::ComplexMatrix2D intermod3Lower;
    RsaToolbox::ComplexMatrix2D intermod3Upper;
    RsaToolbox::ComplexMatrix2D intermod3Major;

    bool isIM5()    const;
    RsaToolbox::ComplexMatrix2D intermod5Lower;
    RsaToolbox::ComplexMatrix2D intermod5Upper;
    RsaToolbox::ComplexMatrix2D intermod5Major;

    bool isIM7()    const;
    RsaToolbox::ComplexMatrix2D intermod7Lower;
    RsaToolbox::ComplexMatrix2D intermod7Upper;
    RsaToolbox::ComplexMatrix2D intermod7Major;

    bool isIM9()    const;
    RsaToolbox::ComplexMatrix2D intermod9Lower;
    RsaToolbox::ComplexMatrix2D intermod9Upper;
    RsaToolbox::ComplexMatrix2D intermod9Major;

    // Intercept Points
    bool isIP3()    const;
    bool isIP5()    const;
    bool isIP7()    const;
    bool isIP9()    const;
    RsaToolbox::ComplexMatrix2D intercept3Major;
    RsaToolbox::ComplexMatrix2D intercept5Major;
    RsaToolbox::ComplexMatrix2D intercept7Major;
    RsaToolbox::ComplexMatrix2D intercept9Major;

private:
    IntermodSettings _settings;
    uint _maxOrder;
    void initialize();
};

#endif // INTERMODDATA_H
