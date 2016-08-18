#include "CombinerEdit.h"
#include "ui_CombinerEdit.h"

CombinerEdit::CombinerEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CombinerEdit)
{
    ui->setupUi(this);

    ui->at->setCurrentText("External");

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

IntermodCombiner CombinerEdit::combiner() const {
    IntermodCombiner ic;
    if (at() == IntermodCombiner::At::External) {
        ic.setExternal();
    }
    else {
        ic.setPort(port());
    }
    return ic;
}

void CombinerEdit::setCombiner(IntermodCombiner combiner) {
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
