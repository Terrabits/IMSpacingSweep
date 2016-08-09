#include "IntermodChannels.h"


// RsaToolbox
using namespace RsaToolbox;


IntermodChannels::IntermodChannels(RsaToolbox::Vna *vna, uint baseChannel) :
    _vna     (vna        ),
    _base    (baseChannel),
    _usedBase(false      )
{
//    collapse();
}

IntermodChannels::~IntermodChannels()
{

}

uint IntermodChannels::base() const {
    return _base;
}

QVector<uint> IntermodChannels::all() {
    QString suffix = "_im_ch%1";
    suffix = suffix.arg(_base);

    QVector<uint>       _all;
    const QVector<uint>  channels = _vna->channels();
    foreach (const uint c, channels) {
        const QString name = _vna->channel(c).name();
        if (name.endsWith(suffix, Qt::CaseInsensitive)) {
            _all << c;
        }
    }
    return _all;
}
VnaChannel IntermodChannels::create(const IntermodTrace &t) {
    // Use or create
    _vna->channel(_base).select();
    uint i;
    if (!_usedBase) {
        VnaChannel ch = _vna->channel(_base);
        const QStringList  traces = ch.traces();
        _vna->deleteTraces(traces);

        i = _base;
        _usedBase = true;
    }
    else {
        i = _vna->createChannel();
    }

    // Channel instance
    VnaChannel c;
    c = _vna->channel(i);

    // Name
    QString name = "%1_im_ch%2";
    name = name.arg(t.abbreviate());
    name = name.arg(_base);
    c.setName(name);

    return c;
}

void IntermodChannels::collapse() {
    // Delete all associated
    // channels except base
    QVector<uint> _most = all();
    if (_most.contains(_base)) {
        const int i = _most.indexOf(_base);
        _most.remove(i);
    }

    _vna->deleteChannels(_most);
    deleteTraces();
    _usedBase = false;
}

void IntermodChannels::deleteTraces() {
    VnaChannel  c      = _vna->channel(_base);
    QStringList traces = c.traces();
    _vna->deleteTraces(traces);
}

QString IntermodChannels::name(const IntermodTrace &t) {
    QString s = "%1_im_ch%2";
    s = s.arg(t.abbreviate());
    s = s.arg(_base);
    return s;
}
