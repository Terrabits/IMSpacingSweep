#include "IntermodTraceDelegate.h"


// Project
#include "IntermodTrace.h"
#include "IntermodTraceModel.h"

// RsaToolbox
#include <FrequencyEdit.h>
#include <General.h>
using namespace RsaToolbox;

// Qt
#include <QComboBox>
#include <QLineEdit>
#include <QRegExp>
#include <QRegExpValidator>


IntermodTraceDelegate::IntermodTraceDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
    //
}

IntermodTraceDelegate::~IntermodTraceDelegate()
{
    //
}

QWidget *IntermodTraceDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    const int row    = index.row();
    const int column = index.column();
    const IntermodTraceModel *model = qobject_cast<const IntermodTraceModel*>(index.model());
    if (!model)
        return 0;

    IntermodTrace trace = model->traces()[row];
    switch (column) {
    case IntermodTraceModel::Column::name: {
        QLineEdit *edit = new QLineEdit(parent);
        QRegExpValidator *vld8r
                = new QRegExpValidator(IntermodTrace::NAME_REGEX,
                                       edit);
        edit->setValidator(vld8r);
        return edit;
    }
    case IntermodTraceModel::Column::y: {
        QComboBox *combo = new QComboBox(parent);
        combo->setEditable(false);
        combo->addItems(trace.possibleYParameters());
        return combo;
    }
    case IntermodTraceModel::Column::x: {
        QComboBox *combo = new QComboBox(parent);
        combo->setEditable(false);
        combo->addItems(trace.possibleXParameters());
        return combo;
    }
    case IntermodTraceModel::Column::at: {
        QComboBox *combo = new QComboBox(parent);
        combo->setEditable(false);
        combo->addItems(trace.possibleAtParameters());
        return combo;
    }
    case IntermodTraceModel::Column::atValue: {
        FrequencyEdit *edit = new FrequencyEdit(parent);
        QRowVector freqs;
        if (trace.isAtDistance()) {
            const double start  = _settings.startToneDistance_Hz();
            const double stop   = _settings.stopToneDistance_Hz();
            const uint   points = _settings.toneDistancePoints();
            freqs               = linearSpacing(start, stop, points);
        }
        else if (trace.isAtCenter()) {
            const double start  = _settings.startCenterFrequency_Hz();
            const double stop   = _settings.stopCenterFrequency_Hz();
            const uint   points = _settings.centerFrequencyPoints();
            freqs               = linearSpacing(start, stop, points);
        }
        edit->setAcceptedValues(freqs);
        connect(edit, SIGNAL(outOfRange(QString)),
                this, SIGNAL(errorMessage(QString)));
        return edit;
    }
    default: {
        return QStyledItemDelegate::createEditor(parent, option, index);
    }
    }
}
void IntermodTraceDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    QComboBox; // Y, X, At
    QLineEdit; // Name
    FrequencyEdit; // At

    QComboBox *combo = qobject_cast<QComboBox*>(editor);
    if (combo) {
        combo->setCurrentText(index.data(Qt::EditRole).toString());
        return;
    }

    QLineEdit *line = qobject_cast<QLineEdit*>(editor);
    if (line) {
        line->setText(index.data(Qt::EditRole).toString());
        return;
    }

    FrequencyEdit *freq = qobject_cast<FrequencyEdit*>(editor);
    if (freq) {
        freq->setFrequency(index.data(Qt::EditRole).toDouble());
        return;
    }

    // Else?
    QStyledItemDelegate::setEditorData(editor, index);
}
void IntermodTraceDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    QComboBox *combo = qobject_cast<QComboBox*>(editor);
    if (combo) {
        model->setData(index, combo->currentText());
        return;
    }

    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(editor);
    if (lineEdit) {
        if (lineEdit->hasAcceptableInput())
            model->setData(index, lineEdit->text());
        return;
    }

    FrequencyEdit *freq = qobject_cast<FrequencyEdit*>(editor);
    if (freq) {
        if (freq->hasAcceptableInput())
            model->setData(index, freq->frequency_Hz());
        return;
    }

    // Else?
    QStyledItemDelegate::setModelData(editor, model, index);
}
void IntermodTraceDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
    // Why not:
    //   QStyledItemDelegate::updateEditorGeometry(...)?
    //   ... why overload at all?
}

void IntermodTraceDelegate::setIntermodSettings(const IntermodSettings &settings) {
    _settings = settings;
}
