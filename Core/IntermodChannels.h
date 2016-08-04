#ifndef INTERMODCHANNELS_H
#define INTERMODCHANNELS_H


// Project
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

    QVector<uint> all();
    RsaToolbox::VnaChannel create(const IntermodTrace &t);

    // Remove all except base
    void collapse();

private:
    RsaToolbox::Vna *_vna;
    uint             _base;
    bool             _usedBase;

    QString name(const IntermodTrace &t);
};

#endif // INTERMODCHANNELS_H
