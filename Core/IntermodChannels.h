#ifndef INTERMODCHANNELS_H
#define INTERMODCHANNELS_H


// Project
#include "FrequencyConversionGenerator.h"
#include "IntermodSettings.h"
#include "IntermodTrace.h"

// RsaToolbox
#include <Vna.h>
#include <VnaChannel.h>

// Qt
#include <Qt>
#include <QRegExp>
#include <QString>
#include <QVector>


class IntermodChannels
{
public:
    IntermodChannels(RsaToolbox::Vna *vna, uint baseChannel);
    ~IntermodChannels();

    uint base() const;

    QVector<uint> all();
    RsaToolbox::VnaChannel create(const IntermodTrace &t);

    // Remove all except base
    // Removes traces in base as well
    void collapse();

private:
    RsaToolbox::Vna *_vna;
    uint             _base;
    bool             _usedBase;

    void deleteTraces();

    QString name(const IntermodTrace &t);
};

#endif // INTERMODCHANNELS_H
