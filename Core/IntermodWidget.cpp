#include "IntermodWidget.h"
#include "ui_IntermodWidget.h"


// Project
#include "IntermodTrace.h"

// RsaToolbox
#include "General.h"
#include <VnaChannel.h>
using namespace RsaToolbox;

// Qt
#include <QDebug>
#include <QLabel>
#include <QList>

// std lib
#include <cassert>


IntermodWidget::IntermodWidget(RsaToolbox::Vna *vna, QWidget *parent) :
    WizardPage(parent),
    ui(new ::Ui::IntermodWidget),
    _vna(vna)
{
    ui->setupUi(this);
    setInputLimits();
    connectWidgets();
}

IntermodWidget::~IntermodWidget()
{
    delete ui;
}

void IntermodWidget::showError(const IntermodError &error) {
    focusOn(error);
    ui->error->showMessage(error.message);
}
void IntermodWidget::showErrorMessage(const QString &message) {
    ui->error->showMessage(message);
}

void IntermodWidget::setInputLimits() {
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

void IntermodWidget::alignLabels() {

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
    /// FIX !!!!! ///
    if (ui->upperSourceIndex->text().isEmpty()) {
        ui->upperSourceIndex->selectAll();
        ui->upperSourceIndex->setFocus();
        error.code = IntermodError::Code::UpperSource;
        error.message = "*Enter upper source";
        return false;
    }
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
        error.code = IntermodError::Code::Points;
        error.message = "*Enter tone distance points";
        return false;
    }

    // Misc
    if (ui->ifBw->text().isEmpty()) {
        ui->ifBw->setFocus();
        error.code = IntermodError::Code::IfBw;
        error.message = "*Enter IF bandwidth";
        return false;
    }
    if (ui->power->text().isEmpty()) {
        ui->power->setFocus();
        error.code = IntermodError::Code::Power;
        error.message = "*Enter power level";
        return false;
    }
    if (ui->selectivity->currentText().isEmpty()) {
        ui->selectivity->setFocus();
        error.code = IntermodError::Code::Selectivity;
        error.message = "*Enter IF selectivity";
        return false;
    }

    // No error
    return true;
}
IntermodSettings IntermodWidget::getInput() const {
    VnaIntermod::ToneSource upper;
    IntermodSettings s;

    // Ports
    s.setLowerSourcePort(ui->lowerPort->points());
    /// FIX !!!!! ////
    upper.setPort(ui->upperSourceIndex->points());
    s.setUpperSource(upper);
    s.setReceivingPort(ui->receivingPort->points());

    // Center frequency
//    s.setStartCenterFrequency(ui->startCenterFrequency->frequency_Hz());
//    s.setStopCenterFrequency(ui->stopCenterFrequency->frequency_Hz());
//    s.setCenterFrequencyPoints(ui->centerFrequencyPoints->points());

    // Tone distance
    s.setStartToneDistance(ui->startToneDistance->frequency_Hz());
    s.setStopToneDistance(ui->stopToneDistance->frequency_Hz());
    s.setPoints(ui->toneDistancePoints->points());

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
//    ui->startCenterFrequency->setFrequency(settings.startCenterFrequency_Hz());
//    ui->stopCenterFrequency->setFrequency(settings.stopCenterFrequency_Hz());
//    ui->centerFrequencyPoints->setPoints(settings.centerFrequencyPoints());

    // Tone distance
    ui->startToneDistance->setFrequency(settings.startToneDistance_Hz());
    ui->stopToneDistance->setFrequency(settings.stopToneDistance_Hz());
    ui->toneDistancePoints->setPoints(settings.points());

    // Misc
    ui->power->setPower(settings.power_dBm());
    ui->ifBw->setFrequency(settings.ifBw_Hz());
    if (settings.selectivity() == VnaChannel::IfSelectivity::Normal)
        ui->selectivity->setCurrentText("Normal");
    else
        ui->selectivity->setCurrentText("High");
}

bool IntermodWidget::isReadyForNext() {
    // Check for missing input
    IntermodError e;
    if (!isInput(e)) {
        emit error(e);
        return false;
    }

    // Check for input error (out of range)
    e.clear();
    IntermodSettings     settings = getInput();
    // Is valid?
    assert(false);
    if (owns(e)) {
        emit error(e);
        return false;
    }

    // Input is good. Ready.
    emit validatedInput(settings);
    return true;
}

void IntermodWidget::showEvent(QShowEvent *event) {
    Q_UNUSED(event);
    QList<QLabel*> labels;
    labels << ui->lowerLabel
           << ui->upperLabel
           << ui->receivingLabel
           << ui->startCenterLabel
           << ui->stopCenterLabel
           << ui->centerPointsLabel
           << ui->startDistanceLabel
           << ui->stopDistanceLabel
           << ui->distancePointsLabel
           << ui->ifBwLabel
           << ui->powerLabel
           << ui->selectivityLabel;

    QList<int> labelWidths;
    foreach (QLabel *label, labels) {
        labelWidths << label->width();
    }

    uint width = max(labelWidths.toVector());

    foreach (QLabel *label, labels) {
        label->setMinimumWidth(width);
    }
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
    connect(ui->power, SIGNAL(outOfRange  (QString)),
            this,      SIGNAL(errorMessage(QString)));
    connect(ui->ifBw,  SIGNAL(outOfRange  (QString)),
            this,      SIGNAL(errorMessage(QString)));

    // Display errors on widget
    connect(this, SIGNAL(error            (IntermodError)),
            this, SLOT  (showError        (IntermodError)));
    connect(this, SIGNAL(errorMessage     (QString      )),
            this, SLOT  (showErrorMessage (QString      )));
}

bool IntermodWidget::owns(const IntermodError &error) {
    typedef IntermodError::Code Code;
    switch(error.code) {
    case Code::LowerSourcePort:
    case Code::UpperSource:
    case Code::ReceivingPort:
    case Code::StartCenterFreq:
    case Code::StopCenterFreq:
    case Code::CenterFreqPoints:
    case Code::StartToneDistance:
    case Code::StopToneDistance:
    case Code::ToneDistancePoints:
    case Code::Power:
    case Code::IfBw:
    case Code::Selectivity:
        return true;
    default:
        return false;
    }
}

void IntermodWidget::focusOn(const IntermodError &error) {
    typedef IntermodError::Code Code;
    switch(error.code) {
    case Code::LowerSourcePort:
        ui->lowerPort->selectAll();
        ui->lowerPort->setFocus();
        break;
    case Code::UpperSource:
        ui->upperSourceIndex->selectAll();
        ui->upperSourceIndex->setFocus();
        break;
    case Code::ReceivingPort:
        ui->receivingPort->selectAll();
        ui->receivingPort->setFocus();
        break;
    case Code::StartCenterFreq:
        ui->startCenterFrequency->selectAll();
        ui->startCenterFrequency->setFocus();
        break;
    case Code::StopCenterFreq:
        ui->stopCenterFrequency->selectAll();
        ui->stopCenterFrequency->setFocus();
        break;
    case Code::CenterFreqPoints:
        ui->centerFrequencyPoints->selectAll();
        ui->centerFrequencyPoints->setFocus();
        break;
    case Code::StartToneDistance:
        ui->startToneDistance->selectAll();
        ui->startToneDistance->setFocus();
        break;
    case Code::StopToneDistance:
        ui->stopToneDistance->selectAll();
        ui->stopToneDistance->setFocus();
        break;
    case Code::ToneDistancePoints:
        ui->toneDistancePoints->selectAll();
        ui->toneDistancePoints->setFocus();
        break;
    case Code::Power:
        ui->power->selectAll();
        ui->power->setFocus();
        break;
    case Code::IfBw:
        ui->ifBw->selectAll();
        ui->ifBw->setFocus();
        break;
    case Code::Selectivity:
        ui->selectivity->setFocus();
        break;
    default:
        break;
    }
}
