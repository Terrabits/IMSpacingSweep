#include "IntermodMeasurement.h"


// RsaToolbox
#include <VnaChannel.h>
using namespace RsaToolbox;


// IntermodError class
IntermodError::IntermodError() :
    code(IntermodError::Code::None)
{
    //
}
IntermodError::~IntermodError()
{
    //
}

bool IntermodError::isError() const {
    return code != Code::None;
}

//IntermodMeasurement class
IntermodMeasurement::IntermodMeasurement(Vna *vna,
                                         uint referenceChannel,
                                         const IntermodSettings &settings,
                                         QObject *parent) :
    Measurement(parent),
    _vna(vna),
    _refChannel(referenceChannel),
    _settings(settings)
{
    //
}
IntermodMeasurement::~IntermodMeasurement()
{
    //
}

bool IntermodMeasurement::isValid(IntermodError &error) const {
    return true;
}

void IntermodMeasurement::run() {
    _vna->isError();
    _vna->clearStatus();

    // Create new channel
    _vna->channel(_refChannel).select();
    uint c = _vna->createChannel();
    VnaChannel channel = _vna->channel(c);

    // Channel
    channel.manualSweepOn();
    channel.setSweepType(VnaChannel::SweepType::Linear);

    // IM settings
    VnaIntermod im = channel.intermod();
    im.setLowerTonePort(_settings.lowerSourcePort());
    im.setUpperToneSource(_settings.upperSource());
    im.setReceivingPort(_settings.receivingPort());

    // Traces????
    im.order3On();
    im.order5On();
    im.order7On();
    im.order9On();
    // Traces????

    // Sweep
    VnaLinearSweep sweep = channel.linearSweep();
    sweep.setPoints(_settings.centerFrequencyPoints());
    sweep.setIfbandwidth(_settings.ifBw_Hz());
    sweep.setPower(_settings.power_dBm());
    _vna->isError();

    const uint timeout_ms = 2 * channel.totalSweepTime_ms() + 5000;
    QRowVector spacings_Hz = linearSpacing(_settings.startSpacing_Hz(), _settings.stopSpacing_Hz(), _settings.spacingPoints());
    for (int i = 0; i < spacings_Hz.size(); i++) {
        const double spacing_Hz = spacings_Hz[i];
        sweep.setStart(_settings.startCenterFrequency_Hz() - 0.5 * spacing_Hz);
        sweep.setStop(_settings.stopCenterFrequency_Hz()   - 0.5 * spacing_Hz);
        im.setToneDistance(spacing_Hz);
        _vna->isError();

        channel.startSweep();
        _vna->pause(timeout_ms);
        _vna->isError();
    }
}
