#include "IntermodTraceDelegate.h"


// Project
#include "IntermodTraceModel.h"

// RsaToolbox
#include <FrequencyEdit.h>
#include <General.h>
using namespace RsaToolbox;

// Qt
#include <QComboBox>
#include <QDebug>
#include <QVariant>


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
    if (!model) {
        return QStyledItemDelegate::createEditor(parent, option, index);
    }

    const IntermodTrace trace = model->traces()[row];
    typedef IntermodTraceModel::Column Column;
    switch (column) {
    case Column::Type:
        return createTypeEditor   (parent);
    case Column::Feature:
        return createFeatureEditor(parent, trace);
    case Column::Order:
        return createOrderEditor  (parent);
    default:
        return QStyledItemDelegate::createEditor(parent, option, index);
    }
}
void IntermodTraceDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    QComboBox *combo = qobject_cast<QComboBox*>(editor);
    if (!combo) {
        QStyledItemDelegate::setEditorData(editor, index);
        return;
    }

    const QString text = index.data().toString();
    combo->setCurrentText(text);
}
void IntermodTraceDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    QComboBox *combo = qobject_cast<QComboBox*>(editor);
    if (!combo) {
        qDebug() << "  ...not a combo!";
        QStyledItemDelegate::setModelData(editor, model, index);
        return;
    }

    const QString text = combo->currentText();
    const int column = index.column();
    typedef IntermodTraceModel::Column Column;
    QVariant value;
    switch (column) {
    case Column::Type:
        value = QVariant::fromValue(toTraceType(text));
        model->setData(index, value);
        break;
    case Column::Feature:
        value = QVariant::fromValue(toTraceFeature(text));
        model->setData(index, value);
        break;
    case Column::Order:
        model->setData(index, text.toUInt());
        break;
    }
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

QWidget *IntermodTraceDelegate::createTypeEditor(QWidget *parent) {
    QStringList items;
    items << toString(TraceType::inputTone      )
          << toString(TraceType::outputTone     )
          << toString(TraceType::intermod       )
          << toString(TraceType::relative       )
          << toString(TraceType::inputIntercept )
          << toString(TraceType::outputIntercept);

    QComboBox *combo = new QComboBox(parent);
    combo->addItems(items);
    return combo;
}
QWidget *IntermodTraceDelegate::createFeatureEditor(QWidget *parent, const IntermodTrace &t) {
    QStringList items;
    items << toString(TraceFeature::lower)
             << toString(TraceFeature::upper);
    if (!t.isInputTone() || !t.isOutputTone())
        items << toString(TraceFeature::major);

    QComboBox *combo = new QComboBox(parent);
    combo->addItems(items);
    return combo;
}
QWidget *IntermodTraceDelegate::createOrderEditor(QWidget *parent) {
    QStringList items;
    items << "3" << "5" << "7" << "9";

    QComboBox *combo = new QComboBox(parent);
    combo->addItems(items);
    return combo;
}
