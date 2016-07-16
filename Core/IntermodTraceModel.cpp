#include "IntermodTraceModel.h"


// RsaToolbox
#include <Definitions.h>
#include <General.h>
using namespace RsaToolbox;


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
    case Column::name:
        return "Name";
    case Column::y:
        return "Y";
    case Column::x:
        return "X";
    case Column::at:
        return "At";
    case Column::atValue:
    default:
        return QVariant();
    }
}
QModelIndex IntermodTraceModel::index(int row, int column, const QModelIndex &parent) const {
    if (parent.isValid())
        return QModelIndex();
    if (row < 0 || row >= _traces.size())
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

    const int row    = index.row();
    const int column = index.column();

    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    switch (column) {
    case Column::name:
    case Column::y:
        return flags | Qt::ItemIsEditable;
    case Column::x:
        if (_traces[row].possibleXParameters().size() > 1)
            return flags | Qt::ItemIsEditable;
        else
            return flags;
    case Column::at:
        if (_traces[row].possibleAtParameters().size() > 1)
            return flags | Qt::ItemIsEditable;
        else
            return flags;
    case Column::atValue:
        if (_traces[row].isAtValue())
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

    const int row = index.row();
    const int column = index.column();
    if (row < 0 || row >= _traces.size())
        return QVariant();
    if (column < 0 || column >= COLUMNS)
        return QVariant();

    if  (role != Qt::DisplayRole
      && role != Qt::EditRole
      && role != Qt::DecorationRole)
    {
        return QVariant();
    }
    else if (role == Qt::DecorationRole) {
        return QVariant();
    }


    IntermodTrace trace = _traces[row];
    switch (column) {
    case Column::name:
        return trace.name();
    case Column::y:
        return trace.y();
    case Column::x:
        return trace.x();
    case Column::at:
        return trace.at();
    case Column::atValue:
        if (!trace.isAtValue()) {
            return QVariant();
        }
        if (role == Qt::EditRole){
            return trace.atValue();
        }
        else {
            return formatValue(trace.atValue(), 3, Units::Hertz);
        }
    default:
        return QVariant();
    }
}
bool IntermodTraceModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid())
        return false;
    if (index.model() != this)
        return false;

    if (role != Qt::EditRole)
        return false;
    if (!value.isValid())
        return false;

    const int row = index.row();
    const int column = index.column();
    if (row < 0 || row >= _traces.size())
        return false;
    if (column < 0 || column >= COLUMNS)
        return false;

    if (column == atValue && !value.canConvert<double>())
        return false;
    else if (!value.canConvert<QString>())
        return false;

    const QString  string = value.toString();
    const double   dbl    = value.toDouble();
    IntermodTrace &trace  = _traces[row];
    QModelIndex topLeft = createIndex(row, 0);
    QModelIndex bottomRight = createIndex(row, COLUMNS-1);
    switch (column) {
    case Column::name:
        if (string.toLower() == trace.name().toLower())
            return true;

        trace.setName(string);
        emit dataChanged(topLeft, bottomRight);
        return true;

    case Column::y:
        if (string.toLower() == trace.y())
            return true;

        trace.setY(string);
        emit dataChanged(topLeft, bottomRight);
        return true;

    case Column::x:
        if (trace.x().compare(value.toString()) == 0)
            return true;
        trace.setX(string);
//        fixTraceSettings(row);
        emit dataChanged(topLeft, bottomRight);
        return true;

    case Column::at:
        if (string.toLower() == trace.at().toLower())
            return true;

        trace.setAt(string);
//        fixTraceSettings(row);
        emit dataChanged(topLeft, bottomRight);
        return true;

    case Column::atValue:
        if (trace.atValue() == dbl)
            return true;
        trace.setAtValue(dbl);
//        fixTraceSettings(row);
        emit dataChanged(index, index);
        return true;
    }

    // Default
    return false;
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

    IntermodTrace trace;
    trace.setY(trace.possibleYParameters().first());
    trace.setX(trace.possibleXParameters().first());
    trace.setAt(trace.possibleAtParameters().first());
    beginInsertRows(parent, row, row + count - 1);
    for (int i = 0; i < count; i++)
        _traces.insert(row, IntermodTrace());
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

// Accessors
QList<IntermodTrace> IntermodTraceModel::traces() const {
    return _traces;
}
void IntermodTraceModel::setTraces(const QList<IntermodTrace> &traces) {
    beginResetModel();
    _traces = traces;
    endResetModel();
}
