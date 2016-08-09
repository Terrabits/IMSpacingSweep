#ifndef IMSETTINGS_H
#define IMSETTINGS_H


// RsaToolbox
#include <VnaChannel.h>
#include <VnaIntermod.h>

// Qt
#include <Qt>


class IntermodSettings
{
public:
    IntermodSettings ();
    ~IntermodSettings();

    // Ports
    uint                                lowerSourcePort() const;
    RsaToolbox::VnaIntermod::ToneSource upperSource    () const;
    uint                                receivingPort  () const;
    void setLowerSourcePort(uint port);
    void setUpperSource(RsaToolbox::VnaIntermod::ToneSource source);
    void setReceivingPort(uint port);

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


#endif // IMSETTINGS_H
