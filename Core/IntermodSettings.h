#ifndef IMSETTINGS_H
#define IMSETTINGS_H


// Project
#include "IntermodCombiner.h"

// RsaToolbox
#include <VnaChannel.h>
#include <VnaIntermod.h>

// Qt
#include <Qt>
#include <QDataStream>


class IntermodSettings
{
public:
    IntermodSettings ();
    ~IntermodSettings();

    // Ports
    uint                                 lowerSourcePort() const;
    RsaToolbox::VnaIntermod::ToneSource  upperSource    () const;
    RsaToolbox::VnaIntermod::ToneSource &upperSource    ();
    uint                                 receivingPort  () const;
    IntermodCombiner                     combiner       () const;
    IntermodCombiner                    &combiner       ();
    void setLowerSourcePort(uint port);
    void setUpperSource  (RsaToolbox::VnaIntermod::ToneSource source);
    void setReceivingPort(uint port);
    void setCombiner     (IntermodCombiner combiner);

    // Center frequency
    double centerFrequency_Hz() const;
    void   setCenterFrequency(double frequency, RsaToolbox::SiPrefix prefix = RsaToolbox::SiPrefix::None);

    // Tone spacing (distance)
    double startToneDistance_Hz() const;
    double stopToneDistance_Hz () const;
    uint   points              () const;
    void   setStartToneDistance(double frequency_Hz, RsaToolbox::SiPrefix prefix = RsaToolbox::SiPrefix::None);
    void   setStopToneDistance (double frequency_Hz, RsaToolbox::SiPrefix prefix = RsaToolbox::SiPrefix::None);
    void   setPoints           (uint points);
    RsaToolbox::QRowVector toneDistances_Hz() const;

    // Measurement settings
    double power_dBm() const;
    double ifBw_Hz()   const;
    RsaToolbox::VnaChannel::IfSelectivity selectivity() const;
    void setPower(double power_dBm);
    void setIfBw(double frequency_Hz, RsaToolbox::SiPrefix prefix = RsaToolbox::SiPrefix::None);
    void setSelectivity(RsaToolbox::VnaChannel::IfSelectivity selectivity);

    // Channel
    uint channel() const;
    void setChannel(uint index);

private:
    // Ports
    uint _lowerSourcePort;
    RsaToolbox::VnaIntermod::ToneSource _upperSource;
    IntermodCombiner _combiner;
    uint _receivingPort;

    // Center frequency
    double _centerFrequency_Hz;

    // Tone spacing
    double _startToneDistance_Hz;
    double _stopToneDistance_Hz;
    uint   _points;

    // Settings
    double _power_dBm;
    double _ifBw_Hz;
    RsaToolbox::VnaChannel::IfSelectivity _selectivity;

    // Channel
    uint _channel;
};

QDataStream &operator<<(QDataStream &stream, const IntermodSettings &settings);
QDataStream &operator>>(QDataStream &stream, IntermodSettings &settings);


#endif // IMSETTINGS_H
