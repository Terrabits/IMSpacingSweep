#include "UpperSourceEdit.h"
#include "ui_UpperSourceEdit.h"


// RsaToolbox
using namespace RsaToolbox;

UpperSourceEdit::UpperSourceEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UpperSourceEdit)
{
    ui->setupUi(this);

    setFocusProxy(ui->type);

    ui->type->clear();
    ui->type->addItem("Port");
    ui->type->setCurrentText("Port");
    ui->type->setDisabled(true);

    ui->port->setParameterName("Upper port");
    ui->port->setMaximum(4);
    ui->port->clear();

    ui->generator->setParameterName("Upper generator");
    ui->generator->clear();

    _isGenerators = false;

    connect(ui->port, SIGNAL(outOfRange(QString)),
            this,     SIGNAL(outOfRange(QString)));
    connect(ui->generator, SIGNAL(outOfRange(QString)),
            this,          SIGNAL(outOfRange(QString)));
}
UpperSourceEdit::~UpperSourceEdit()
{
    delete ui;
}

// Public
bool UpperSourceEdit::isInput() const {
    if (isPort())
        return !ui->port->text().isEmpty();
    else
        return !ui->generator->text().isEmpty();
}
void UpperSourceEdit::setValue(VnaIntermod::ToneSource source) {
    if (source.isPort()) {
        bool isBlocked = blockSignals(true);
        ui->type->setCurrentText("Port");
        ui->port->setPoints(source.port());
        blockSignals(isBlocked);
    }
    else if (source.isGenerator()) {
        bool isBlocked = blockSignals(true);
        ui->type->setCurrentText("Generator");
        ui->generator->setPoints(source.generator());
        blockSignals(isBlocked);
    }
    else {
        bool isBlocked = blockSignals(true);
        ui->type->setCurrentText("Port");
        ui->port->clear();
        ui->generator->clear();
        blockSignals(isBlocked);
    }
}

VnaIntermod::ToneSource UpperSourceEdit::value() const {
    if (!isInput())
        return VnaIntermod::ToneSource();

    VnaIntermod::ToneSource src;
    if (isPort()) {
        src.setPort(port());
    }
    else {
        src.setGenerator(generator());
    }
    return src;
}

void UpperSourceEdit::setVnaPorts(uint numberOfPorts) {
    bool isBlocked = blockSignals(true);
    _ports = numberOfPorts;
    ui->port->setMaximum(_ports);
    blockSignals(isBlocked);
}
void UpperSourceEdit::setGenerators(uint numberOfGenerators) {
    _generators = numberOfGenerators;
    enableGenerator();
    selectGenerator();
}
void UpperSourceEdit::clearGenerators() {
    if (!_isGenerators)
        return;

    _isGenerators = false;
    _generators   = 0;

    bool isBlocked = blockSignals(true);
    ui->type->clear();
    ui->type->addItem("Port");
    ui->type->setCurrentText("Port");
    ui->type->setDisabled(true);
    ui->stackedWidget->setCurrentWidget(ui->portPage);
    ui->generator->clear();
    blockSignals(isBlocked);
}

// public slots
void UpperSourceEdit::selectAll() {
    if (isPort())
        ui->port->selectAll();
    else
        ui->generator->selectAll();
}

// Private slots
void UpperSourceEdit::on_type_currentIndexChanged(const QString &arg1) {
    Q_UNUSED(arg1);
    if (isPort())
        selectPort();
    else
        selectGenerator();
}

// Private
void UpperSourceEdit::selectPort() {
    bool isBlocked = blockSignals(true);
    ui->type->setCurrentText("Port");
    ui->stackedWidget->setCurrentWidget(ui->portPage);
    blockSignals(isBlocked);
}
void UpperSourceEdit::enableGenerator() {
    bool isBlocked = blockSignals(true);
    ui->generator->setMaximum(_generators);
    if (!_isGenerators) {
        _isGenerators = true;
        ui->type->addItem("Generator");
        ui->type->setEnabled(true);
    }
    blockSignals(isBlocked);
}
void UpperSourceEdit::selectGenerator() {
    bool isBlocked = blockSignals(true);
    ui->type->setCurrentText("Generator");
    ui->stackedWidget->setCurrentWidget(ui->generatorPage);
    blockSignals(isBlocked);
}

bool UpperSourceEdit::isPort() const {
    return ui->type->currentText().toLower() == "port";
}
uint UpperSourceEdit::port() const {
    return ui->port->points();
}
uint UpperSourceEdit::generator() const {
    return ui->generator->points();
}
