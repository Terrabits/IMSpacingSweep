#include "ProcessTracesWidget.h"
#include "ui_ProcessTracesWidget.h"


// Project
#include "ProcessThread.h"
#include "ProcessTraces.h"

// RsaToolbox
using namespace RsaToolbox;

// Qt
#include <QDebug>


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
    buttons()->hide();
    _process.reset(new ProcessThread(_settings, _traces, _vna));
    QObject::connect(_process.data(), SIGNAL(finished()),
                     this, SLOT(processFinished()));
    _process->start();
}

void ProcessTracesWidget::setSettings(const IntermodSettings &settings) {
    _settings = settings;
}
void ProcessTracesWidget::setTraces(const IntermodTraces &traces) {
    _traces = traces;
}

void ProcessTracesWidget::processFinished() {
    wizard()->close();
}
