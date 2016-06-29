#include "IntermodWidget.h"
#include "ui_IntermodWidget.h"


// RsaToolbox
#include <VnaChannel.h>
using namespace RsaToolbox;

// Qt
#include <QDebug>


IntermodWidget::IntermodWidget(RsaToolbox::Vna *vna, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IntermodWidget),
    _vna(vna)
{
    ui->setupUi(this);
    initialize();
    connectWidgets();
}

IntermodWidget::~IntermodWidget()
{
    delete ui;
}

void IntermodWidget::initialize() {
    // Ports
    const uint ports = _vna->properties().physicalPorts();
    ui->lowerPort->setMaximum(ports);
    qDebug() << "Need uppper source widget and/or some mechanism...";
    ui->upperSourceIndex->setMaximum(ports);
    ui->receivingPort->setMaximum(ports);

    // Center frequency
    const double min_Hz  = _vna->properties().minimumFrequency_Hz();
    const double max_Hz  = _vna->properties().maximumFrequency_Hz();
    const uint maxPoints = _vna->properties().maximumPoints();
    ui->startCenterFrequency->setMinimum(min_Hz);
    ui->startCenterFrequency->setMaximum(max_Hz);
    ui->stopCenterFrequency->setMinimum(min_Hz);
    ui->stopCenterFrequency->setMaximum(max_Hz);
    ui->centerFrequencyPoints->setMaximum(maxPoints);

    // Distance
    ui->startToneDistance->setMaximum(max_Hz);
    ui->stopToneDistance->setMaximum(max_Hz);
    ui->toneDistancePoints->setMaximum(maxPoints);

    // Misc
    ui->ifBw->setAcceptedValues(_vna->properties().ifBandwidthValues_Hz());
    ui->power->setMinimum(_vna->properties().minimumPower_dBm());
    ui->power->setMaximum(_vna->properties().maximumPower_dBm());
}

bool IntermodWidget::isInput(IntermodError &error) const {
    error.clear();

    // Ports
    if (ui->lowerPort->text().isEmpty()) {
        ui->lowerPort->setFocus();
        error.code = IntermodError::Code::LowerSourcePort;
        error.message = "*Enter lower source port";
        return false;
    }
//    if (ui->upperSource->isEmpty()) {
//        ui->upperSource->setFocus();
//        error.code = IntermodError::Code::UpperSource;
//        error.message = "*Enter upper source";
//        return false;
//    }
    if (ui->receivingPort->text().isEmpty()) {
        ui->receivingPort->setFocus();
        error.code = IntermodError::Code::ReceivingPort;
        error.message = "*Enter receiving port";
        return false;
    }

    // Center frequency
    if (ui->startCenterFrequency->text().isEmpty()) {
        ui->startCenterFrequency->setFocus();
        error.code = IntermodError::Code::StartCenterFreq;
        error.message = "*Enter start center frequency";
        return false;
    }
    if (ui->stopCenterFrequency->text().isEmpty()) {
        ui->stopCenterFrequency->setFocus();
        error.code = IntermodError::Code::StopCenterFreq;
        error.message = "*Enter stop center frequency";
        return false;
    }
    if (ui->centerFrequencyPoints->text().isEmpty()) {
        ui->centerFrequencyPoints->setFocus();
        error.code = IntermodError::Code::CenterFreqPoints;
        error.message = "*Enter center frequency points";
        return false;
    }

    // Tone distance
    if (ui->startToneDistance->text().isEmpty()) {
        ui->startToneDistance->setFocus();
        error.code = IntermodError::Code::StartToneDistance;
        error.message = "*Enter start tone distance";
        return false;
    }
    if (ui->stopToneDistance->text().isEmpty()) {
        ui->stopToneDistance->setFocus();
        error.code = IntermodError::Code::StopToneDistance;
        error.message = "*Enter stop tone distance";
        return false;
    }
    if (ui->toneDistancePoints->text().isEmpty()) {
        ui->toneDistancePoints->setFocus();
        error.code = IntermodError::Code::ToneDistancePoints;
        error.message = "*Enter tone distance points";
        return false;
    }

    // Misc
    if (ui->power->text().isEmpty()) {
        ui->power->setFocus();
        error.code = IntermodError::Code::Power;
        error.message = "*Enter power level";
        return false;
    }
    if (ui->ifBw->text().isEmpty()) {
        ui->ifBw->setFocus();
        error.code = IntermodError::Code::IfBw;
        error.message = "*Enter IF bandwidth";
        return false;
    }
    if (ui->selectivity->currentText().isEmpty()) {
        ui->selectivity->setFocus();
        error.code = IntermodError::Code::Selectivity;
        error.message = "*Enter IF selectivity";
        return false;
    }

    return true;
}
IntermodSettings IntermodWidget::getInput() const {
    IntermodSettings s;

    // Ports
    s.setLowerSourcePort(ui->lowerPort->points());
//    s.setUpperSource(ui->upperSource->?);
    s.setReceivingPort(ui->receivingPort->points());

    // Center frequency
    s.setStartCenterFrequency(ui->startCenterFrequency->frequency_Hz());
    s.setStopCenterFrequency(ui->stopCenterFrequency->frequency_Hz());
    s.setCenterFrequencyPoints(ui->centerFrequencyPoints->points());

    // Tone distance
    s.setStartToneDistance(ui->startToneDistance->frequency_Hz());
    s.setStopToneDistance(ui->stopToneDistance->frequency_Hz());
    s.setToneDistancePoints(ui->toneDistancePoints->points());

    // Misc
    s.setPower(ui->power->power_dBm());
    s.setIfBw(ui->ifBw->frequency_Hz());
    if (ui->selectivity->currentText() == "Normal")
        s.setSelectivity(VnaChannel::IfSelectivity::Normal);
    else
        s.setSelectivity(VnaChannel::IfSelectivity::High);

    return s;
}
void IntermodWidget::setInput(const IntermodSettings &settings) {
    // Ports
    ui->lowerPort->setPoints(settings.lowerSourcePort());
//    ui->upperSource->set?...
    ui->receivingPort->setPoints(settings.receivingPort());

    // Center Frequency
    ui->startCenterFrequency->setFrequency(settings.startCenterFrequency_Hz());
    ui->stopCenterFrequency->setFrequency(settings.stopCenterFrequency_Hz());
    ui->centerFrequencyPoints->setPoints(settings.centerFrequencyPoints());

    // Tone distance
    ui->startToneDistance->setFrequency(settings.startToneDistance_Hz());
    ui->stopToneDistance->setFrequency(settings.stopToneDistance_Hz());
    ui->toneDistancePoints->setPoints(settings.toneDistancePoints());

    // Misc
    ui->power->setPower(settings.power_dBm());
    ui->ifBw->setFrequency(settings.ifBw_Hz());
    if (settings.selectivity() == VnaChannel::IfSelectivity::Normal)
        ui->selectivity->setCurrentText("Normal");
    else
        ui->selectivity->setCurrentText("High");
}

void IntermodWidget::connectWidgets() {
    // Ports
    connect(ui->lowerPort, SIGNAL(outOfRange(QString)),
            this, SIGNAL(errorMessage(QString)));
    connect(ui->upperSourceIndex, SIGNAL(outOfRange(QString)),
            this, SIGNAL(errorMessage(QString)));
    connect(ui->receivingPort, SIGNAL(outOfRange(QString)),
            this, SIGNAL(errorMessage(QString)));

    // Center frequency
    connect(ui->startCenterFrequency, SIGNAL(outOfRange(QString)),
            this, SIGNAL(errorMessage(QString)));
    connect(ui->stopCenterFrequency, SIGNAL(outOfRange(QString)),
            this, SIGNAL(errorMessage(QString)));
    connect(ui->centerFrequencyPoints, SIGNAL(outOfRange(QString)),
            this, SIGNAL(errorMessage(QString)));

    // Tone Distance
    connect(ui->startToneDistance, SIGNAL(outOfRange(QString)),
            this, SIGNAL(errorMessage(QString)));
    connect(ui->stopToneDistance, SIGNAL(outOfRange(QString)),
            this, SIGNAL(errorMessage(QString)));
    connect(ui->toneDistancePoints, SIGNAL(outOfRange(QString)),
            this, SIGNAL(errorMessage(QString)));

    // Misc
    connect(ui->power, SIGNAL(outOfRange(QString)),
            this, SIGNAL(errorMessage(QString)));
    connect(ui->ifBw, SIGNAL(outOfRange(QString)),
            this, SIGNAL(errorMessage(QString)));
}
