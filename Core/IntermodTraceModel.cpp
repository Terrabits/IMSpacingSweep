#include "IntermodTraceModel.h"


// RsaToolbox
#include <Definitions.h>
#include <General.h>
using namespace RsaToolbox;

// Qt
#include <QDebug>


// Constructor/destructor
IntermodTraceModel::IntermodTraceModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    //
}

IntermodTraceModel::~IntermodTraceModel()
{
    //
}

// Model
QVariant IntermodTraceModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (section < 0 || section >= COLUMNS)
        return QVariant();
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Vertical)
        return QVariant();

    switch (section) {
    case Column::Type:
        return "Type";
    case Column::Feature:
        return "Feature";
    case Column::Order:
        return "Order";
    default:
        return QVariant();
    }
}
QModelIndex IntermodTraceModel::index(int row, int column, const QModelIndex &parent) const {
    if (parent.isValid())
        return QModelIndex();
    if (row    < 0 || row    >= _traces.size())
        return QModelIndex();
    if (column < 0 || column >= COLUMNS)
        return QModelIndex();

    return createIndex(row, column);
}
QModelIndex IntermodTraceModel::parent(const QModelIndex &child) const {
    Q_UNUSED(child);
    return QModelIndex();
}
Qt::ItemFlags IntermodTraceModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::ItemFlags();

    const int column = index.column();

    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    const IntermodTrace t = _traces[index.row()];
    switch (column) {
    case Column::Type:
    case Column::Feature:
        return flags | Qt::ItemIsEditable;
    case Column::Order:
        if (t.hasOrder())
            return flags | Qt::ItemIsEditable;
        else
            return flags;
    default:
        return flags;
    }
}

int IntermodTraceModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;
    else
        return _traces.size();
}
int IntermodTraceModel::columnCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;
    else
        return COLUMNS;
}

QVariant IntermodTraceModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();
    if (index.model() != this)
        return QVariant();

    const int row    = index.row();
    const int column = index.column();
    switch (column) {
    case Column::Type:
        return getType   (row, role);
    case Column::Feature:
        return getFeature(row, role);
    case Column::Order:
        return getOrder  (row, role);
    default:
        return QVariant();
    }
}
bool IntermodTraceModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid()) {
        return false;
    }
    if (index.model() != this) {
        return false;
    }

    if (role != Qt::EditRole && role != Qt::DisplayRole) {
        return false;
    }
    if (!value.isValid()) {
        return false;
    }

    const int row    = index.row   ();
    const int column = index.column();
    if (row < 0 || row >= _traces.size()) {
        return false;
    }
    if (column < 0 || column >= COLUMNS) {
        return false;
    }

    const TraceType    type    = value.value<TraceType>   ();
    const TraceFeature feature = value.value<TraceFeature>();
    const uint         order   = value.toUInt();
    IntermodTrace     &trace   = _traces[row];
    switch (column) {
    case Column::Type:
        trace.setType(type);
        emit dataChanged(index, index);
        return true;
    case Column::Feature:
        trace.setFeature(feature);
        emit dataChanged(index, index);
        return true;
    case Column::Order:
        if (!trace.hasOrder())
            return false;
        trace.setOrder(order);
        emit dataChanged(index, index);
        return true;
    default:
        return false;
    }
}

bool IntermodTraceModel::appendNewTrace() {
    if (_traces.isEmpty()) {
        return insertRow(0);
    }

    const int row = _traces.size();
    return insertRow(row);
}
bool IntermodTraceModel::moveRowUp(int row) {
    if (_traces.isEmpty())
        return false;
    if (row < 1)
        return false;
    const int last = _traces.size()-1;
    if (row > last)
        return false;

    IntermodTrace trace = _traces[row];
    beginResetModel();
    _traces.removeAt(row);
    _traces.insert(row-1, trace);
    endResetModel();
    return true;
}
bool IntermodTraceModel::moveRowDown(int row) {
    if (_traces.isEmpty())
        return false;
    if (row < 0)
        return false;
    const int last = _traces.size()-1;
    if (row >= last)
        return false;

    IntermodTrace trace = _traces[row];
    beginResetModel();
    _traces.removeAt(row);
    _traces.insert(row+1, trace);
    endResetModel();
    return true;
}

bool IntermodTraceModel::insertRows(int row, int count, const QModelIndex &parent) {
    if (parent.isValid())
        return false;
    if (row < 0 || row > _traces.size())
        return false;
    if (count < 0)
        return false;
    if (count == 0)
        return true;

    beginInsertRows(parent, row, row + count - 1);
    for (int i = 0; i < count; i++) {
        _traces.insert(row, IntermodTrace());
    }
    endInsertRows();
    return true;
}
bool IntermodTraceModel::removeRows(int row, int count, const QModelIndex &parent) {
    if (parent.isValid())
        return false;
    if (row < 0 || row >= _traces.size())
        return false;
    if (count < 0)
        return false;
    if (count == 0)
        return true;
    const int lastRow = row + count - 1;
    if (lastRow >= _traces.size())
        return false;

    beginRemoveRows(parent, row, lastRow);
    for (int i = 0; i < count; i++)
        _traces.removeAt(row);
    endRemoveRows();
    return true;
}

void IntermodTraceModel::setSettings(const IntermodSettings &settings) {
    beginResetModel();
    _settings = settings;
    endResetModel();
}

// Accessors
QList<IntermodTrace> IntermodTraceModel::traces() const {
    return _traces;
}
void IntermodTraceModel::setTraces(const QList<IntermodTrace> &traces) {
    beginResetModel();
    _traces = traces;
    endResetModel();
}

QVariant IntermodTraceModel::getType(int row, int role) const {
    const TraceType t = _traces[row].type();
    if (role == Qt::DisplayRole)
        return toString(t);
    if (role == Qt::EditRole)
        return QVariant::fromValue(t);

    // Else
    return QVariant();
}
QVariant IntermodTraceModel::getFeature(int row, int role) const {
    const TraceFeature f = _traces[row].feature();
    if (role == Qt::DisplayRole)
        return toString(f);
    if (role == Qt::EditRole)
        return QVariant::fromValue(f);

    // Else
    return QVariant();
}
QVariant IntermodTraceModel::getOrder(int row, int role) const {
    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    const IntermodTrace t = _traces[row];
    if (t.hasOrder())
        return t.order();
    else
        return QVariant();
}
