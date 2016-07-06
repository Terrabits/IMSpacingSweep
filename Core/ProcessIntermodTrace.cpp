#include "ProcessIntermodTrace.h"


// RsaToolbox
using namespace RsaToolbox;


void processIntermodTrace(RsaToolbox::Vna *vna, IntermodTrace trace, IntermodData &data) {
    const QString name  = trace.name();
    const QString _name = "_" + name;

    // Channel
    const uint c = vna->createChannel();
    VnaChannel channel = vna->channel(c);
    channel.setName(_name);
    channel.setSweepType(VnaChannel::SweepType::Linear);
    channel.setIfSelectivity(data.settings().selectivity());

    VnaLinearSweep sweep = channel.linearSweep();
    sweep.setStart();
    sweep.setStop();
    sweep.setPoints();
    sweep.setIfbandwidth(data.settings().ifBw_Hz());
    sweep.setPower(data.settings().power_dBm());


    // Data trace
    vna->createTrace(c, _name);
    vna->trace(_name).setParameter("UTI");

    // Memory trace
    vna->trace(_name).toMemory(name);
    vna->trace(name).write(values);
}

