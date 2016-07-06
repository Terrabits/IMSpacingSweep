#include "WriteIntermodTrace.h"


// RsaToolbox
using namespace RsaToolbox;


void writeIntermodTrace(RsaToolbox::Vna *vna, IntermodTrace trace, IntermodData &data) {
    const QString name  = trace.name();
    const QString _name = "_" + name;

    // FIX /////////
    const QRowVector       x = data.centerFrequencies_Hz();
    const ComplexRowVector y = column(0, data.intermod5Lower);

    // Channel
    const uint c = vna->createChannel();
    VnaChannel channel = vna->channel(c);
    channel.manualSweepOn();
    channel.setName(_name);
    channel.setSweepType(VnaChannel::SweepType::Linear);
    channel.setIfSelectivity(data.settings().selectivity());

    VnaLinearSweep sweep = channel.linearSweep();
    sweep.setStart (x.first());
    sweep.setStop  (x.last() );
    sweep.setPoints(x.size() );
    sweep.setIfbandwidth(data.settings().ifBw_Hz());
    sweep.setPower(data.settings().power_dBm());

    // Data trace
    vna->createTrace(_name, c);
    vna->trace(_name).setParameter("UTI");

    // Memory trace
    vna->trace(_name).toMemory(name);
    vna->trace(name).write(y);
}

