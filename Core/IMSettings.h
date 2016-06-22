#ifndef IMSETTINGS_H
#define IMSETTINGS_H


// RsaToolbox
#include <VnaChannel.h>
#include <VnaIntermod.h>

// Qt
#include <Qt>


class IMSettings
{
public:
    IMSettings();

    // Ports
    uint                                lowerSourcePort() const;
    RsaToolbox::VnaIntermod::ToneSource upperSource()     const;
    uint                                receivingPort()   const;
    void setLowerSourcePort(uint port);
    void setUpperSource(RsaToolbox::VnaIntermod::ToneSource source);
    void setReceivingPort(uint port);

    // Center frequency
    double startCenterFrequency_Hz() const;
    double stopCenterFrequency_Hz()  const;
    uint   centerFrequencyPoints()   const;
    void setStartCenterFrequency(double frequency_Hz, RsaToolbox::SiPrefix prefix = RsaToolbox::SiPrefix::None);
    void setStopCenterFrequency(double frequency_Hz, RsaToolbox::SiPrefix prefix = RsaToolbox::SiPrefix::None);
    void setCenterFrequencyPoints(uint points);

    // Tone spacing
    double startSpacing_Hz()         const;
    double stopSpacing_Hz()          const;
    uint   spacingPoints()           const;
    void setStartSpacing(double frequency_Hz, RsaToolbox::SiPrefix prefix = RsaToolbox::SiPrefix::None);
    void setStopSpacing(double frequency_Hz, RsaToolbox::SiPrefix prefix = RsaToolbox::SiPrefix::None);
    void setSpacingPoints(uint points);

    // Measurement settings
    double power_dBm() const;
    double ifBw_Hz()   const;
    RsaToolbox::VnaChannel::IfSelectivity selectivity() const;
    void setPower(double power_dBm);
    void setIfBw(double frequency_Hz, RsaToolbox::SiPrefix prefix = RsaToolbox::SiPrefix::None);
    void setSelectivity(RsaToolbox::VnaChannel::IfSelectivity selectivity);

    // Orders/Traces?
    // How to specify?
    // Need here

private:
    // Ports
    uint _lowerSourcePort;
    RsaToolbox::VnaIntermod::ToneSource _upperSource;
    uint _receivingPort;

    // Center frequency
    double _startCenterFreq_Hz;
    double _stopCenterFreq_Hz;
    uint   _centerFrequencyPoints;

    // Tone spacing
    double _start_Hz;
    double _stop_Hz;
    uint   _spacingPoints;

    // Settings
    double _power_dBm;
    double _if_bw_Hz;
    RsaToolbox::VnaChannel::IfSelectivity _selectivity;

    // Orders/Traces?
};


#endif // IMSETTINGS_H
