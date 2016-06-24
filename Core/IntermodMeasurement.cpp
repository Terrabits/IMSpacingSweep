#include "IntermodMeasurement.h"


// RsaToolbox
#include <Test.h>
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
void IntermodError::clear() {
    code = Code::None;
    message.clear();
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

bool IntermodMeasurement::isValid() const {
    IntermodError error;
    return isValid(error);
}
bool IntermodMeasurement::isValid(IntermodError &error) const {
    error.clear();
    return true;
}

void IntermodMeasurement::run() {
    _vna->isError();
    _vna->clearStatus();
    if (!isValid())
        return;

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

    // Sweep
    VnaLinearSweep sweep = channel.linearSweep();
    sweep.setPoints(_settings.centerFrequencyPoints());
    sweep.setIfbandwidth(_settings.ifBw_Hz());
    sweep.setPower(_settings.power_dBm());
    _vna->isError();

    // First sweep settings
    QRowVector spacings_Hz = linearSpacing(_settings.startSpacing_Hz(), _settings.stopSpacing_Hz(), _settings.spacingPoints());
    sweep.setStart(_settings.startCenterFrequency_Hz() - 0.5 * spacings_Hz.first());
    sweep.setStop(_settings.stopCenterFrequency_Hz()   - 0.5 * spacings_Hz.first());
    im.setToneDistance(spacings_Hz.first());
    _vna->isError();

    // Traces
    im.order3On();
    im.order5On();
    im.order7On();
    im.order9On();
    uint diagram = _vna->createDiagram();
    createTraces(c, diagram);

    // Start first sweep
    const uint timeout_ms = 2 * channel.totalSweepTime_ms() + 5000;
    channel.startSweep();
    _vna->pause(timeout_ms);
    _vna->isError();

    // Read first sweep data
    readData();

    // Continue with the rest of the sweeps
    for (int i = 1; i < spacings_Hz.size(); i++) {
        const double spacing_Hz = spacings_Hz[i];
        sweep.setStart(_settings.startCenterFrequency_Hz() - 0.5 * spacing_Hz);
        sweep.setStop(_settings.stopCenterFrequency_Hz()   - 0.5 * spacing_Hz);
        im.setToneDistance(spacing_Hz);
        _vna->isError();

        channel.startSweep();
        _vna->pause(timeout_ms);
        _vna->isError();

        // Take data
        readData();
    }

    deleteTraces();
    if (_vna->isDiagram(diagram))
        _vna->deleteDiagram(diagram);
    _vna->deleteChannel(c);
}

void IntermodMeasurement::createTraces(uint channel, uint diagram) {
    _lti = _vna->createTrace(channel);
    _lto = _vna->createTrace(channel);
    _uti = _vna->createTrace(channel);
    _uto = _vna->createTrace(channel);
    _vna->trace(_lti).setIntermodTone(VnaTrace::Side::Lower, VnaTrace::At::Input);
    _vna->trace(_lti).setIntermodTone(VnaTrace::Side::Lower, VnaTrace::At::Output);
    _vna->trace(_lti).setIntermodTone(VnaTrace::Side::Upper, VnaTrace::At::Input);
    _vna->trace(_lti).setIntermodTone(VnaTrace::Side::Upper, VnaTrace::At::Output);
    _vna->trace(_lti).setDiagram(diagram);
    _vna->trace(_lto).setDiagram(diagram);
    _vna->trace(_uti).setDiagram(diagram);
    _vna->trace(_uto).setDiagram(diagram);

    _im3l = _vna->createTrace(channel);
    _im5l = _vna->createTrace(channel);
    _im7l = _vna->createTrace(channel);
    _im9l = _vna->createTrace(channel);
    _vna->trace(_im3l).setIntermod(3, VnaTrace::Side::Lower);
    _vna->trace(_im5l).setIntermod(5, VnaTrace::Side::Lower);
    _vna->trace(_im7l).setIntermod(7, VnaTrace::Side::Lower);
    _vna->trace(_im9l).setIntermod(9, VnaTrace::Side::Lower);
    _vna->trace(_im3l).setDiagram(diagram);
    _vna->trace(_im5l).setDiagram(diagram);
    _vna->trace(_im7l).setDiagram(diagram);
    _vna->trace(_im9l).setDiagram(diagram);

    _im3u = _vna->createTrace(channel);
    _im5u = _vna->createTrace(channel);
    _im7u = _vna->createTrace(channel);
    _im9u = _vna->createTrace(channel);
    _vna->trace(_im3u).setIntermod(3, VnaTrace::Side::Upper);
    _vna->trace(_im5u).setIntermod(5, VnaTrace::Side::Upper);
    _vna->trace(_im7u).setIntermod(7, VnaTrace::Side::Upper);
    _vna->trace(_im9u).setIntermod(9, VnaTrace::Side::Upper);
    _vna->trace(_im3u).setDiagram(diagram);
    _vna->trace(_im5u).setDiagram(diagram);
    _vna->trace(_im7u).setDiagram(diagram);
    _vna->trace(_im9u).setDiagram(diagram);

    _im3m = _vna->createTrace(channel);
    _im5m = _vna->createTrace(channel);
    _im7m = _vna->createTrace(channel);
    _im9m = _vna->createTrace(channel);
    _vna->trace(_im3m).setIntermod(3, VnaTrace::Side::Major);
    _vna->trace(_im5m).setIntermod(5, VnaTrace::Side::Major);
    _vna->trace(_im7m).setIntermod(7, VnaTrace::Side::Major);
    _vna->trace(_im9m).setIntermod(9, VnaTrace::Side::Major);
    _vna->trace(_im3m).setDiagram(diagram);
    _vna->trace(_im5m).setDiagram(diagram);
    _vna->trace(_im7m).setDiagram(diagram);
    _vna->trace(_im9m).setDiagram(diagram);

    _ip3m = _vna->createTrace(channel);
    _ip5m = _vna->createTrace(channel);
    _ip7m = _vna->createTrace(channel);
    _ip9m = _vna->createTrace(channel);
    _vna->trace(_ip3m).setIntermodIntercept(3, VnaTrace::Side::Major);
    _vna->trace(_ip3m).setIntermodIntercept(5, VnaTrace::Side::Major);
    _vna->trace(_ip3m).setIntermodIntercept(7, VnaTrace::Side::Major);
    _vna->trace(_ip3m).setIntermodIntercept(9, VnaTrace::Side::Major);
    _vna->trace(_ip3m).setDiagram(diagram);
    _vna->trace(_ip5m).setDiagram(diagram);
    _vna->trace(_ip7m).setDiagram(diagram);
    _vna->trace(_ip9m).setDiagram(diagram);
}
void IntermodMeasurement::deleteTraces() {
    _vna->deleteTrace(_lti);
    _vna->deleteTrace(_lto);
    _vna->deleteTrace(_uti);
    _vna->deleteTrace(_uto);

    _vna->deleteTrace(_im3l);
    _vna->deleteTrace(_im5l);
    _vna->deleteTrace(_im7l);
    _vna->deleteTrace(_im9l);

    _vna->deleteTrace(_im3u);
    _vna->deleteTrace(_im5u);
    _vna->deleteTrace(_im7u);
    _vna->deleteTrace(_im9u);

    _vna->deleteTrace(_im3m);
    _vna->deleteTrace(_im5m);
    _vna->deleteTrace(_im7m);
    _vna->deleteTrace(_im9m);

    _vna->deleteTrace(_ip3m);
    _vna->deleteTrace(_ip5m);
    _vna->deleteTrace(_ip7m);
    _vna->deleteTrace(_ip9m);
    _vna->pause();
}

void IntermodMeasurement::readData() {
    _vna->trace(_lti).y();
    _vna->trace(_lto).y();
    _vna->trace(_uti).y();
    _vna->trace(_uto).y();

    _vna->trace(_im3l).y();
    _vna->trace(_im5l).y();
    _vna->trace(_im7l).y();
    _vna->trace(_im9l).y();

    _vna->trace(_im3u).y();
    _vna->trace(_im5u).y();
    _vna->trace(_im7u).y();
    _vna->trace(_im9u).y();

    _vna->trace(_im3m).y();
    _vna->trace(_im5m).y();
    _vna->trace(_im7m).y();
    _vna->trace(_im9m).y();
}
