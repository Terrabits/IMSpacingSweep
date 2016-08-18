#include "IntermodWidget.h"
#include "ui_IntermodWidget.h"


// Project
#include "IntermodTrace.h"
#include "ProcessTraces.h"

// RsaToolbox
#include "General.h"
#include <VnaChannel.h>
using namespace RsaToolbox;

// Qt
#include <QDebug>
#include <QLabel>
#include <QList>
#include <QVariant>

// std lib
#include <cassert>


IntermodWidget::IntermodWidget(RsaToolbox::Vna *vna, Keys *keys, QWidget *parent) :
    WizardPage(parent),
    ui(new ::Ui::IntermodWidget),
    _vna (vna ),
    _keys(keys)
{
    ui->setupUi(this);

    setInputLimits();
    loadKeys      ();
    connectWidgets();
}

IntermodWidget::~IntermodWidget()
{
    delete ui;
}

void IntermodWidget::saveInput() {
    saveKeys();
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
    qDebug() << "Need upper source widget and/or some mechanism...";
    ui->upperSourceIndex->setMaximum(ports);
    qDebug() << "Need better ZVA combiner test";
    if (_vna->properties().isZvaFamily())
        ui->combiner->enablePort();
    ui->combiner->setVnaPorts(_vna->properties().physicalPorts());
    ui->receivingPort->setMaximum(ports);

    // Center frequency
    const double min_Hz  = _vna->properties().minimumFrequency_Hz();
    const double max_Hz  = _vna->properties().maximumFrequency_Hz();
    ui->centerFrequency->setMinimum(min_Hz);
    ui->centerFrequency->setMaximum(max_Hz);

    // Tone Distance
    const uint maxPoints = _vna->properties().maximumPoints();
    ui->startToneDistance->setMaximum(max_Hz);
    ui->stopToneDistance->setMaximum(max_Hz);
    ui->toneDistancePoints->setMaximum(maxPoints);

    // Misc
    ui->ifBw->setAcceptedValues(_vna->properties().ifBandwidthValues_Hz());
    ui->power->setMinimum(_vna->properties().minimumPower_dBm());
    ui->power->setMaximum(_vna->properties().maximumPower_dBm());

    ui->channel->clear   ( );
    ui->channel->addItems(toStringList(_vna->channels()));
}

bool IntermodWidget::isValidInput(IntermodError &e) const {
    e.clear();

    // Ports
    if (ui->lowerPort->text().isEmpty()) {
        ui->lowerPort->setFocus();
        e.code = IntermodError::Code::LowerSourcePort;
        e.message = "*Enter lower source port";
        return false;
    }
    // FIX ME !!!!! ///
    if (ui->upperSourceIndex->text().isEmpty()) {
        ui->upperSourceIndex->selectAll();
        ui->upperSourceIndex->setFocus();
        e.code = IntermodError::Code::UpperSource;
        e.message = "*Enter upper source";
        return false;
    }
    if (ui->combiner->isPortEmpty()) {
        ui->combiner->setPortFocus();
        e.code = IntermodError::Code::Combiner;
        e.message = "*Enter combiner port";
        return false;
    }
    if (ui->receivingPort->text().isEmpty()) {
        ui->receivingPort->setFocus();
        e.code = IntermodError::Code::ReceivingPort;
        e.message = "*Enter receiving port";
        return false;
    }

    // Center frequency
    if (ui->centerFrequency->text().isEmpty()) {
        ui->centerFrequency->setFocus();
        e.code = IntermodError::Code::CenterFrequency;
        e.message = "*Enter center frequency";
        return false;
    }

    // Tone distance
    if (ui->startToneDistance->text().isEmpty()) {
        ui->startToneDistance->setFocus();
        e.code = IntermodError::Code::StartToneDistance;
        e.message = "*Enter start tone distance";
        return false;
    }
    if (ui->stopToneDistance->text().isEmpty()) {
        ui->stopToneDistance->setFocus();
        e.code = IntermodError::Code::StopToneDistance;
        e.message = "*Enter stop tone distance";
        return false;
    }
    if (ui->toneDistancePoints->text().isEmpty()) {
        ui->toneDistancePoints->setFocus();
        e.code = IntermodError::Code::Points;
        e.message = "*Enter tone distance points";
        return false;
    }

    // Misc
    if (ui->ifBw->text().isEmpty()) {
        ui->ifBw->setFocus();
        e.code = IntermodError::Code::IfBw;
        e.message = "*Enter IF bandwidth";
        return false;
    }
    if (ui->power->text().isEmpty()) {
        ui->power->setFocus();
        e.code = IntermodError::Code::Power;
        e.message = "*Enter power level";
        return false;
    }
    if (ui->selectivity->currentText().isEmpty()) {
        ui->selectivity->setFocus();
        e.code = IntermodError::Code::Selectivity;
        e.message = "*Enter IF selectivity";
        return false;
    }
    if (ui->channel->currentText().isEmpty()) {
        ui->channel->setFocus();
        e.code = IntermodError::Code::Channel;
        e.message = "*Choose channel";
        return false;
    }

    QList<IntermodTrace> traces;
    ProcessTraces p(traces, input(), _vna);
    p.isReady(e);
    if (owns(e))
        return false;

    e.clear();
    return true;
}
IntermodSettings IntermodWidget::input() const {
    IntermodSettings s;

    // Ports
    s.setLowerSourcePort(ui->lowerPort->points());
    // FIX ME !!!!! ////
    s.upperSource().setPort(ui->upperSourceIndex->points());
    s.setCombiner(ui->combiner->value());
    s.setReceivingPort(ui->receivingPort->points());

    // Center frequency
    s.setCenterFrequency(ui->centerFrequency->frequency_Hz());

    // Tone distance
    s.setStartToneDistance(ui->startToneDistance->frequency_Hz());
    s.setStopToneDistance(ui->stopToneDistance->frequency_Hz());
    s.setPoints(ui->toneDistancePoints->points());

    // Misc
    s.setPower(ui->power->power_dBm());
    s.setIfBw(ui->ifBw->frequency_Hz());
    s.setSelectivity(selectivity());
    s.setChannel(channel());

    return s;
}
void IntermodWidget::setInput(const IntermodSettings &settings) {
    // Ports
    ui->lowerPort->setPoints(settings.lowerSourcePort());
    // FIX ME !!!!
    ui->upperSourceIndex->setPoints(settings.upperSource().port());
    ui->combiner->setValue(settings.combiner());
    ui->receivingPort->setPoints(settings.receivingPort());

    // Center Frequency
    ui->centerFrequency->setFrequency(settings.centerFrequency_Hz());

    // Tone distance
    ui->startToneDistance->setFrequency(settings.startToneDistance_Hz());
    ui->stopToneDistance->setFrequency(settings.stopToneDistance_Hz());
    ui->toneDistancePoints->setPoints(settings.points());

    // Misc
    ui->power->setPower(settings.power_dBm());
    ui->ifBw->setFrequency(settings.ifBw_Hz());
    setSelectivity(settings.selectivity());
    setChannel(settings.channel());
}

bool IntermodWidget::isReadyForNext() {
    IntermodError err;
    if (!isValidInput(err)) {
        emit error(err);
        return false;
    }

    emit validatedInput(input());
    return true;
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
    connect(ui->centerFrequency, SIGNAL(outOfRange(QString)),
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
void IntermodWidget::loadKeys() {
    if (!_keys)
        return;
    if (!_keys->exists("SETTINGS"))
        return;

    IntermodSettings settings;
    _keys->get("SETTINGS", settings);
    setInput(settings);
}
void IntermodWidget::saveKeys() {
    if (!_keys)
        return;

    _keys->set("SETTINGS", input());
}

// Input
VnaChannel::IfSelectivity IntermodWidget::selectivity() const {
    const QString s = ui->selectivity->currentText();
    if (s == "Normal")
        return VnaChannel::IfSelectivity::Normal;
    else
        return VnaChannel::IfSelectivity::High;
}
void IntermodWidget::setSelectivity(VnaChannel::IfSelectivity s) {
    if (s == VnaChannel::IfSelectivity::Normal)
        ui->selectivity->setCurrentText("Normal");
    else
        ui->selectivity->setCurrentText("High");
}
uint IntermodWidget::channel() const {
    const QString s = ui->channel->currentText();
    return s.toUInt();
}
void IntermodWidget::setChannel(uint index) {
    if (!_vna->channels().contains(index))
        return;

    const QString s = QVariant(index).toString();
    ui->channel->setCurrentText(s);
}

bool IntermodWidget::owns(const IntermodError &error) {
    typedef IntermodError::Code Code;
    switch(error.code) {
    case Code::LowerSourcePort:
    case Code::UpperSource:
    case Code::ReceivingPort:
    case Code::CenterFrequency:
    case Code::StartToneDistance:
    case Code::StopToneDistance:
    case Code::Points:
    case Code::Power:
    case Code::IfBw:
    case Code::Selectivity:
    case Code::Channel:
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
    case Code::CenterFrequency:
        ui->centerFrequency->selectAll();
        ui->centerFrequency->setFocus();
        break;
    case Code::StartToneDistance:
        ui->startToneDistance->selectAll();
        ui->startToneDistance->setFocus();
        break;
    case Code::StopToneDistance:
        ui->stopToneDistance->selectAll();
        ui->stopToneDistance->setFocus();
        break;
    case Code::Points:
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
    case Code::Channel:
        ui->channel->setFocus();
        break;
    default:
        break;
    }
}
