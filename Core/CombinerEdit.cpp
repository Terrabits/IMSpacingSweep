#include "CombinerEdit.h"
#include "ui_CombinerEdit.h"

CombinerEdit::CombinerEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CombinerEdit)
{
    ui->setupUi(this);

    ui->at->clear();
    ui->at->addItem("External");
    ui->at->setCurrentText("External");
    ui->at->setDisabled(true);

    ui->port->setParameterName("Combiner port");
    ui->port->clear();
    ui->port->hide();
    connect(ui->port, SIGNAL(outOfRange(QString)),
            this,     SIGNAL(outOfRange(QString)));
}
CombinerEdit::~CombinerEdit()
{
    delete ui;
}

void CombinerEdit::setVnaPorts(uint numberOfPorts) {
    ui->port->setMinimum(1);
    ui->port->setMaximum(numberOfPorts);
}

bool CombinerEdit::isPortEnabled() const {
    return ui->at->count() == 2;
}
bool CombinerEdit::isPortEmpty() const {
    if (!isPortEnabled())
        return false;

    return ui->port->text().isEmpty();
}
IntermodCombiner CombinerEdit::value() const {
    IntermodCombiner ic;
    if (at() == IntermodCombiner::At::External) {
        ic.setExternal();
    }
    else {
        ic.setPort(port());
    }
    return ic;
}

void CombinerEdit::enablePort(bool isEnabled) {
    if (isEnabled) {
        if (isPortEnabled())
            return;

        ui->at->addItem("Port");
        ui->at->setEnabled(true);
    }
    else {
        if (!isPortEnabled())
            return;

        ui->at->removeItem(1);
        ui->at->setCurrentText("External");
        ui->at->setDisabled(true);
        ui->port->clear();
    }
}
void CombinerEdit::disablePort(bool isDisabled) {
    enablePort(!isDisabled);
}
void CombinerEdit::setPortFocus() {
    if (at() != IntermodCombiner::At::Port) {
        this->setFocus();
        return;
    }

    ui->port->setFocus();
}

void CombinerEdit::setValue(IntermodCombiner combiner) {
    const QString &at = IntermodCombiner::toString(combiner.at());
    ui->at->setCurrentText(at);

    if (combiner.isPort())
        ui->port->setPoints(combiner.port());
}

void CombinerEdit::on_at_currentIndexChanged(const QString &arg1) {
    if (arg1.toLower() == "external")
        ui->port->hide();
    else
        ui->port->show();
}

IntermodCombiner::At CombinerEdit::at() const {
    return IntermodCombiner::toAt(ui->at->currentText());
}
uint CombinerEdit::port() const {
    return ui->port->points();
}
