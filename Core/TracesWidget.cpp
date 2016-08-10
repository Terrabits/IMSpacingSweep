#include "TracesWidget.h"
#include "ui_TracesWidget.h"


// RsaToolbox
using namespace RsaToolbox;

// Qt
#include <QDebug>


TracesWidget::TracesWidget(Vna *vna, Keys *keys, QWidget *parent) :
    WizardPage(parent),
    ui(new ::Ui::TracesWidget),
    _vna (vna ),
    _keys(keys),
    _keysLoaded(false)
{
    ui->setupUi(this);
    setupMvc      ();
    connectWidgets();
}

TracesWidget::~TracesWidget()
{
    delete ui;
}

bool TracesWidget::isEmpty() const {
    return _model.traces().isEmpty();
}
bool TracesWidget::isValidInput(IntermodError &error) const {
    error.clear();
    if (isEmpty()) {
        ui->addTrace->setFocus();
        error.code = IntermodError::Code::Traces;
        error.message = "*At least one trace is required";
        return false;
    }

    ProcessTraces p(input(), _settings, _vna);
    p.isReady(error);
    if (owns(error))
        return false;

    // No errors
    error.clear();
    return true;
}
IntermodTraces TracesWidget::input() const {
    return _model.traces();
}
void TracesWidget::setInput(const IntermodTraces &traces) {
    _model.setTraces(traces);
}

void TracesWidget::initialize() {
    bool blocked = this->blockSignals(true);
    loadKeys();
    this->blockSignals(blocked);
}
bool TracesWidget::isReadyForNext() {
    IntermodError e;
    if (!isValidInput(e)) {
        emit error(e);
        return false;
    }

    emit validatedInput(input());
    return true;
}

// public slots
void TracesWidget::setSettings(const IntermodSettings &settings) {
    _settings = settings;
    _model.setSettings(_settings);
}

void TracesWidget::saveInput() {
    saveKeys();
}

void TracesWidget::showError(const IntermodError &error) {
    if (owns(error))
        ui->traces->setFocus();
    ui->error->showMessage(error.message);
}
void TracesWidget::showErrorMessage(const QString &message) {
    ui->error->showMessage(message);
}

// private slots
void TracesWidget::addTrace() {
    _model.appendNewTrace();
    const int rows = _model.rowCount();
    ui->traces->selectRow(rows-1);
}
void TracesWidget::deleteTrace() {
    QModelIndex i = ui->traces->currentIndex();
    if (i.isValid())
        _model.removeRow(i.row());
}
void TracesWidget::moveTraceUp() {
    const int row = ui->traces->currentIndex().row();
    if (_model.moveRowUp(row))
        ui->traces->selectRow(row-1);
}
void TracesWidget::moveTraceDown() {
    const int row  = ui->traces->currentIndex().row();
    if (_model.moveRowDown(row))
        ui->traces->selectRow(row+1);
}

bool TracesWidget::owns(const IntermodError &error) const {
    typedef IntermodError::Code Code;
    switch(error.code) {
    case Code::Traces:
    case Code::Order:
        return true;
    default:
        return false;
    }
}
void TracesWidget::setupMvc() {
    ui->traces->setModel       (&_model   );
    ui->traces->setItemDelegate(&_delegate);
}
void TracesWidget::connectWidgets() {
    // Trace buttons
    connect(ui->addTrace,    SIGNAL(clicked()      ),
            this,            SLOT  (addTrace()     ));
    connect(ui->deleteTrace, SIGNAL(clicked()      ),
            this,            SLOT  (deleteTrace()  ));
    connect(ui->moveUp,      SIGNAL(clicked()      ),
            this,            SLOT  (moveTraceUp()  ));
    connect(ui->moveDown,    SIGNAL(clicked()      ),
            this,            SLOT  (moveTraceDown()));

    // Model, delegate error signals
    connect(&_model,    SIGNAL(error(IntermodError )),
             this,      SIGNAL(error(IntermodError )));
    connect(&_delegate, SIGNAL(errorMessage(QString)),
             this,      SIGNAL(errorMessage(QString)));

    // Show errors on Gui
    connect(this, SIGNAL(error    (IntermodError )),
            this, SLOT  (showError(IntermodError )));
    connect(this, SIGNAL(errorMessage    (QString)),
            this, SLOT  (showErrorMessage(QString)));
}

void TracesWidget::loadKeys() {
    if (_keysLoaded)
        return;
    if (!_keys)
        return;
    if (!_keys->exists("TRACES"))
        return;

    IntermodTraces traces;
    _keys->get("TRACES", traces);
    setInput(traces);
    _keysLoaded = true;
}
void TracesWidget::saveKeys() {
    if (!_keys)
        return;

    _keys->set("TRACES", input());
}
