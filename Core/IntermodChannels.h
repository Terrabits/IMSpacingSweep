#ifndef INTERMODCHANNELS_H
#define INTERMODCHANNELS_H


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
    RsaToolbox::VnaChannel create();

    // Remove all except base
    void collapse();

private:
    RsaToolbox::Vna *_vna;
    QString          _nameFormat;
    QRegExp          _nameRegex;
    uint             _base;

    QString nextName();
};

#endif // INTERMODCHANNELS_H
