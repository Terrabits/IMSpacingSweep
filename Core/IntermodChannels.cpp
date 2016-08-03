#include "IntermodChannels.h"


// RsaToolbox
using namespace RsaToolbox;


IntermodChannels::IntermodChannels(RsaToolbox::Vna *vna, uint baseChannel) :
    _vna(vna),
    _nameFormat("intermod%1"),
    _nameRegex("^intermod\\d+$", Qt::CaseInsensitive),
    _base(baseChannel)
{
    _vna->channel(_base).select();
    _vna->channel(_base).setName(nextName());
}

IntermodChannels::~IntermodChannels()
{

}

QVector<uint> IntermodChannels::all() {
    QVector<uint>       _all;
    const QVector<uint>  channels = _vna->channels();
    foreach (const uint c, channels) {
        const QString name = _vna->channel(c).name();
        if (_nameRegex.exactMatch(name)) {
            _all << c;
        }
    }
    return _all;
}
VnaChannel IntermodChannels::create() {
    _vna->channel(_base).select();
    const uint i = _vna->createChannel();

    VnaChannel c;
    c = _vna->channel(i);
    c.setName(nextName());
    return c;
}

void IntermodChannels::collapse() {
    QVector<uint> _most = all();
    if (_most.contains(_base)) {
        const int i = _most.indexOf(_base);
        _most.remove(i);
    }
    _vna->deleteChannels(_most);
}

QString IntermodChannels::nextName() {
    int i = all().size() + 1;
    QString name = _nameFormat.arg(i);
    while (_vna->isChannel(name)) {
        i++;
        name = _nameFormat.arg(i);
    }
    return name;
}
