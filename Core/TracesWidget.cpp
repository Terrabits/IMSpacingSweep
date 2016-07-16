#include "TracesWidget.h"
#include "ui_TracesWidget.h"


// RsaToolbox
using namespace RsaToolbox;

// Qt
#include <QDebug>


TracesWidget::TracesWidget(Vna *vna, QWidget *parent) :
    WizardPage(parent),
    ui(new ::Ui::TracesWidget),
    _vna(vna)
{
    ui->setupUi(this);
    setupMvc();
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
        error.code = IntermodError::Code::Traces;
        error.message = "*At least one trace is required";
        return false;
    }

    // Else
    return /*true*/ false;
}
QList<IntermodTrace> TracesWidget::traces() const {
    return _model.traces();
}
void TracesWidget::setTraces(const QList<IntermodTrace> &traces) {
    _model.setTraces(traces);
}

void TracesWidget::initialize() {

}
void TracesWidget::back() {

}

void TracesWidget::addTrace() {
    _model.appendNewTrace();
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

void TracesWidget::showError(const IntermodError &error) {
    if (!owns(error))
        return;

    const int row       = error.row;
    const int column    = error.column;
    const QModelIndex i = _model.index(row, column);
    ui->traces->setFocus();
    if (i.isValid())
        ui->traces->edit(i);
    ui->error->showMessage(error.message);
}
void TracesWidget::showErrorMessage(const QString &message) {
    ui->error->showMessage(message);
}

void TracesWidget::measure() {
    qDebug() << "measure";
}

bool TracesWidget::owns(const IntermodError &error) const {
    return error.code == IntermodError::Code::Traces;
}
void TracesWidget::setupMvc() {
    ui->traces->setModel       (&_model   );
    ui->traces->setItemDelegate(&_delegate);
}
void TracesWidget::connectWidgets() {
    // Trace buttons
    connect(ui->addTrace,    SIGNAL(clicked()    ),
            this,            SLOT  (addTrace()   ));
    connect(ui->deleteTrace, SIGNAL(clicked()    ),
            this,            SLOT  (deleteTrace()));
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
