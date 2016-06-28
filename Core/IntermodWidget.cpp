#include "IntermodWidget.h"
#include "ui_IntermodWidget.h"


// Qt
#include <QDebug>

IntermodWidget::IntermodWidget(RsaToolbox::Vna *vna, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IntermodWidget),
    _vna(vna)
{
    ui->setupUi(this);
    initialize();
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
