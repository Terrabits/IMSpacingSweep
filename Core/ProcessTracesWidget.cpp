#include "ProcessTracesWidget.h"
#include "ui_ProcessTracesWidget.h"


// Project
#include "ProcessTraces.h"

// RsaToolbox
using namespace RsaToolbox;


ProcessTracesWidget::ProcessTracesWidget(RsaToolbox::Vna *vna, QWidget *parent) :
    WizardPage(parent),
    ui(new ::Ui::ProcessTracesWidget),
    _vna(vna)
{
    ui->setupUi(this);
}

ProcessTracesWidget::~ProcessTracesWidget()
{
    delete ui;
}

void ProcessTracesWidget::initialize() {
    buttons()->next()->setText("Apply");
    QObject::disconnect(buttons()->next(), SIGNAL(clicked()),
                        wizard(), SLOT(next()));
    QObject::connect(buttons()->next(), SIGNAL(clicked()),
                     this, SLOT(run()));
}
void ProcessTracesWidget::back() {
    buttons()->next()->setText("Next");
    QObject::disconnect(buttons()->next(), SIGNAL(clicked()),
                     this, SLOT(run()));
    QObject::connect(buttons()->next(), SIGNAL(clicked()),
                        wizard(), SLOT(next()));
}

void ProcessTracesWidget::setSettings(const IntermodSettings &settings) {
    _settings = settings;
}
void ProcessTracesWidget::setTraces(const QList<IntermodTrace> &traces) {
    _traces = traces;
}

void ProcessTracesWidget::run() {
    ProcessTraces p(_traces, _settings, _vna);
    p.run();
    wizard()->close();
}
