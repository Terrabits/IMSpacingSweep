#include "CalibrateWidget.h"
#include "ui_CalibrateWidget.h"


// RsaToolbox
using namespace RsaToolbox;


CalibrateWidget::CalibrateWidget(Vna *vna, QWidget *parent) :
    WizardPage(parent),
    ui(new ::Ui::CalibrateWidget),
    _vna(vna)
{
    ui->setupUi(this);
}

CalibrateWidget::~CalibrateWidget()
{
    delete ui;
}

void CalibrateWidget::initialize() {
    buttons()->next()->setText("Calibrate");
    QObject::disconnect(buttons()->next(), SIGNAL(clicked()),
                        wizard(), SLOT(next()));

    QObject::connect(buttons()->next(), SIGNAL(clicked()),
                     this, SLOT(setupCalibration()));

    buttons()->customC()->setText("Skip");
    buttons()->customC()->setEnabled(true);
    buttons()->customC()->setVisible(true);
    QObject::connect(buttons()->customC(), SIGNAL(clicked()),
                     wizard(), SLOT(next()));
}
void CalibrateWidget::back() {
    buttons()->next()->setText("Next");
    QObject::disconnect(buttons()->next(), SIGNAL(clicked()),
                     this, SLOT(setupCalibration()));
    QObject::connect(buttons()->next(), SIGNAL(clicked()),
                     wizard(), SLOT(next()));

    buttons()->customC()->setVisible(false);
    QObject::disconnect(buttons()->customC(), SIGNAL(clicked()),
                     wizard(), SLOT(next()));

}
int CalibrateWidget::next() {
    back();
    return WizardPage::next();
}

void CalibrateWidget::setSettings(const IntermodSettings &settings) {
    _settings = settings;
}
void CalibrateWidget::setTraces(const QList<IntermodTrace> &traces) {
    _traces = traces;
}

void CalibrateWidget::setupCalibration() {
    ProcessTraces p(_traces, _settings, _vna);
    p.setupCalibration();
    wizard()->close();
}
