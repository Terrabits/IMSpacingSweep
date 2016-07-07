#include "IntermodFunctions.h"


// RsaToolbox
using namespace RsaToolbox;


void configureChannelForIntermod(Vna *vna, uint channel, IntermodSettings settings) {
    // Channel
    VnaChannel ch = vna->channel(channel);
    vna->settings().powerReductionBetweenSweepsOn();
    ch.manualSweepOn();
    ch.setSweepType(VnaChannel::SweepType::Linear);
    ch.setIfSelectivity(settings.selectivity());

    // Sweep
    VnaLinearSweep sweep = ch.linearSweep();
    sweep.setIfbandwidth(settings.ifBw_Hz());
    sweep.setPower(settings.power_dBm());

    // Intermod
    VnaIntermod im = ch.intermod();
    im.setLowerTonePort(settings.lowerSourcePort());
    im.setUpperToneSource(settings.upperSource());
    im.setReceivingPort(settings.receivingPort());
    im.order3On();
    im.order5On();
    im.order7On();
    im.order9On();
}
