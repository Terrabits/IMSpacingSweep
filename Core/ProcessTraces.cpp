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
    _diagram = _vna->createDiagram();
    preprocessTraces();
    for (int i = 0; i < _traces.size(); i++) {
        processTrace(_traces[i]);
    }
}

ProcessTraces::~ProcessTraces()
{

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
    IntermodTrace t_in (TraceType::inputTone, Feature::lower);
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
    IntermodTrace t_in (TraceType::inputTone, Feature::lower);
    IntermodTrace t_out(TraceType::intermod,  t.feature(), t.order());

    QString expr = "%1 / %2";
    expr = expr.arg(traceName(t_in ));
    expr = expr.arg(traceName(t_out));
    vnaTrc.math().setExpression(expr);
}
