#include "ProcessTraces.h"


// RsaToolbox
#include <VnaChannel.h>
#include <VnaTrace.h>
using namespace RsaToolbox;


ProcessTraces::ProcessTraces(const QList<IntermodTraces> &traces,
                             const IntermodSettings &settings,
                             RsaToolbox::Vna *vna,
                             uint baseChannel)
    : _traces(traces),
      _settings(settings),
      _vna(vna),
      _channels(vna, baseChannel),
      _genFreq(settings)
{
    preprocessTraces();
}

ProcessTraces::~ProcessTraces()
{

}

bool ProcessTraces::isReady(IntermodError &error) {
    error.clear();

    const uint vnaPorts = _vna->testPorts();

    // Lower port
    if (lowerPort() == 0 || lowerPort() > vnaPorts) {
        error.code = IntermodError::Code::LowerSourcePort;
        error.message = "*lower input port is invalid";
        return false;
    }

    // Upper port
    // Need to include generator...
    if (upperPort() == 0 || upperPort() > vnaPorts) {
        error.code = IntermodError::Code::UpperSource;
        error.message = "*upper input is invalid";
        return false;
    }

    // Output
    if (outputPort() == 0 || outputPort() > vnaPorts) {
        error.code = IntermodError::Code::ReceivingPort;
        error.message = "*receiving port is invalid";
        return false;
    }

    // Port overlap
    if (lowerPort() == upperPort()) {
        error.code = IntermodError::Code::UpperSource;
        error.message = "*port assignments overlap";
        return false;
    }
    if (lowerPort() == outputPort()) {
        error.code = IntermodError::Code::LowerSource;
        error.message = "*port assignments overlap";
        return false;
    }
    if (upperPort() == outputPort()) {
        error.code = IntermodError::Code::UpperSource;
        error.message = "*port assignments overlap";
        return false;
    }

    // Center frequency
    const double center_Hz = _settings.centerFrequency_Hz();
    const double min_Hz    = _vna->properties().minimumFrequency_Hz();
    if (center_Hz < min_Hz) {
        error.code = IntermodError::Code::CenterFrequency;
        error.message = "*center frequency too low";
        return false;
    }
    const double max_Hz    = _vna->properties().maximumFrequency_Hz();
    if (center_Hz > max_Hz) {
        error.code = IntermodError::Code::CenterFrequency;
        error.message = "*center frequency too high";
        return false;
    }

    // Tone distance
    const double startDist_Hz = _settings.startToneDistance_Hz();
    const double stopDist_Hz  = _settings.stopToneDistance_Hz ();
    if (startDist_Hz <= 0) {
        error.code = IntermodError::Code::StartToneDistance;
        error.message = "*start tone distance must be greater than 0";
        return false;
    }
    if (stopDist_Hz <= 0) {
        error.code = IntermodError::Code::StopToneDistance;
        error.message = "*stop tone distance must be greater than 0";
        return false;
    }
    if (startDist_Hz >= stopDist_Hz) {
        error.code = IntermodError::Code::StartToneDistance;
        error.message = "*start tone distance must be greater than stop";
        return false;
    }
    if (center_Hz - 0.5 * stopDist_Hz < min_Hz) {
        error.code = IntermodError::Code::StopToneDistance;
        error.message = "*tone distance too wide for VNA";
        return false;
    }
    if (center_Hz + 0.5 * stopDist_Hz > max_Hz) {
        error.code = IntermodError::Code::StopToneDistance;
        error.message = "*tone distance too wide for VNA";
        return false;
    }

    // Points
    const uint points = _settings.points();
    if (points == 0) {
        error.code = IntermodError::Code::Points;
        error.message = "*points must be greater than 0";
        return false;
    }
    const uint maxPoints = _vna->properties().maximumPoints();
    if (points > maxPoints) {
        error.code = IntermodError::Code::Points;
        error.message = "*points must be at most %1";
        error.message = error.message.arg(maxPoints);
        return false;
    }

    // Power
    const double min_dBm = _vna->properties().minimumPower_dBm();

    const double max_dBm = _vna->properties().maximumPower_dBm();


}
void ProcessTraces::run() {
    _diagram = _vna->createDiagram();
    for (int i = 0; i < _traces.size(); i++) {
        processTrace(_traces[i]);
    }
}

void ProcessTraces::preprocessTraces() {
    // make sure all necessary traces,
    // including trace dependencies,
    // are included
}
void ProcessTraces::processTrace(const IntermodTrace &t) {
    switch (t.type()) {
    case TraceType::inputTone:
        processInputTrace(t);
        return;
    case TraceType::outputTone:
        processOutputTrace(t);
        return;
    case TraceType::intermod:
        processIntermodTrace(t);
        return;
    case TraceType::relative:
        processRelativeTrace(t);
        return;
    case TraceType::intercept:
        processInterceptTrace(t);
        return;
    default:
        return;
    }
}

void ProcessTraces::processInputTrace    (const IntermodTrace &t) {
    // Create channel
    const uint iCh   = _channels.create(t);
    VnaChannel vnaCh = _vna->channel(iCh);

    // Port setup
    vnaCh.setArbitraryFrequency(lowerPort(), lowerAf());
    vnaCh.setArbitraryFrequency(upperPort(), upperAf());

    // Trace
    VnaTrace vnaTrc = _vna->createTrace(traceName(t), iCh);
    if (t.isLower()) {
        vnaTrc.setWaveQuantity(WaveQuantity::a, lowerPort(), lowerPort());
    }
    else {
        vnaTrc.setWaveQuantity(WaveQuantity::a, upperPort(), lowerPort());
    }
    t.setDiagram(_diagram);
}
void ProcessTraces::processOutputTrace   (const IntermodTrace &t) {
    // Create channel
    const uint iCh   = _channels.create(t);
    VnaChannel vnaCh = _vna->channel(iCh);

    // Port setup
    vnaCh.setArbitraryFrequency(lowerPort(),  lowerAf ( ));
    vnaCh.setArbitraryFrequency(upperPort(),  upperAf ( ));
    vnaCh.setArbitraryFrequency(outputPort(), outputAf(t));

    // Trace
    VnaTrace vnaTrc = _vna->createTrace(traceName(t), iCh);
    vnaTrc.setWaveQuantity(WaveQuantity::b, outputPort(), lowerPort());
    t.setDiagram(_diagram);
}
void ProcessTraces::processIntermodTrace (const IntermodTrace &t) {
    // Create channel
    const uint iCh   = _channels.create(t);
    VnaChannel vnaCh = _vna->channel(iCh);

    // Port setup
    vnaCh.setArbitraryFrequency(lowerPort(),  lowerAf ( ));
    vnaCh.setArbitraryFrequency(upperPort(),  upperAf ( ));
    vnaCh.setArbitraryFrequency(outputPort(), outputAf(t));

    // Trace
    VnaTrace vnaTrc = _vna->createTrace(traceName(t), iCh);
    vnaTrc.setWaveQuantity(WaveQuantity::b, outputPort(), lowerPort());
    t.setDiagram(_diagram);
}
void ProcessTraces::processRelativeTrace (const IntermodTrace &t) {
    // Create channel
    const uint iCh   = _channels.create(t);
    VnaChannel vnaCh = _vna->channel(iCh);

    // Port setup
    vnaCh.setArbitraryFrequency(lowerPort(),  lowerAf ( ));
    vnaCh.setArbitraryFrequency(upperPort(),  upperAf ( ));
    vnaCh.setArbitraryFrequency(outputPort(), outputAf(t));

    // Trace
    VnaTrace vnaTrc = _vna->createTrace(traceName(t), iCh);
    vnaTrc.setWaveQuantity(WaveQuantity::b, outputPort(), lowerPort());
    t.setDiagram(_diagram);

    // Always use lti?
    // Use mti (major)?
    IntermodTrace t_in (TraceType::inputTone, TraceFeature::lower);
    IntermodTrace t_out(TraceType::intermod,  t.feature(), t.order());

    QString expr = "%1 / %2";
    expr = expr.arg(traceName(t_in ));
    expr = expr.arg(traceName(t_out));
    vnaTrc.math().setExpression(expr);
}
void ProcessTraces::processInterceptTrace(const IntermodTrace &t) {
    // Create channel
    const uint iCh   = _channels.create(t);
    VnaChannel vnaCh = _vna->channel(iCh);

    // Port setup
    vnaCh.setArbitraryFrequency(lowerPort(),  lowerAf ( ));
    vnaCh.setArbitraryFrequency(upperPort(),  upperAf ( ));
    vnaCh.setArbitraryFrequency(outputPort(), outputAf(t));

    // Trace
    VnaTrace vnaTrc = _vna->createTrace(traceName(t), iCh);
    vnaTrc.setWaveQuantity(WaveQuantity::b, outputPort(), lowerPort());
    t.setDiagram(_diagram);

    // How do I even calculate intercept?
    IntermodTrace t_in (TraceType::inputTone, TraceFeature::lower);
    IntermodTrace t_out(TraceType::intermod,  t.feature(), t.order());

    QString expr = "%1 / %2";
    expr = expr.arg(traceName(t_in ));
    expr = expr.arg(traceName(t_out));
    vnaTrc.math().setExpression(expr);
}
