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
      && role != Qt::EditRole)
    {
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
        else {
            if (role == Qt::EditRole) {
                return trace.atValue();
            }
            else {
                return formatValue(trace.atValue(), 3, trace.atUnits());
            }
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
        fixTrace(row);
        emit dataChanged(index, index);
        return true;

    case Column::y:
        if (string.toLower() == trace.y())
            return true;

        trace.setY(string);
        fixTrace(row);
        emit dataChanged(topLeft, bottomRight);
        return true;

    case Column::x:
        if (trace.x().compare(value.toString()) == 0)
            return true;
        trace.setX(string);
        fixTrace(row);
        emit dataChanged(topLeft, bottomRight);
        return true;

    case Column::at:
        if (string.toLower() == trace.at().toLower())
            return true;

        trace.setAt(string);
        fixTrace(row);
        emit dataChanged(topLeft, bottomRight);
        return true;

    case Column::atValue:
        if (trace.atValue() == dbl)
            return true;
        trace.setAtValue(dbl);
        fixTrace(row);
        emit dataChanged(index, index);
        return true;
    }

    // Default
    return false;
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

    IntermodTrace trace;
    trace.setY(trace.possibleYParameters().first());
    trace.setX(trace.possibleXParameters().first());
    trace.setAt(trace.possibleAtParameters().first());
    trace.setAtValue(trace.possibleAtValues(_settings).first());
    beginInsertRows(parent, row, row + count - 1);
    for (int i = 0; i < count; i++) {
        trace.setName(nextTraceName());
        _traces.insert(row, trace);
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
    _settings = settings;
    fixTraces();
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

bool IntermodTraceModel::hasTraceName(const QString &name) const {
    for (int i = 0; i < _traces.size(); i++) {
        if (_traces[i].name().toLower() == name.toLower())
            return true;
    }
    return false;
}
QString IntermodTraceModel::nextTraceName() const {
    if (_traces.isEmpty()) {
        return "Trc1";
    }

    const QString format = "Trc%1";
    int i = _traces.size()+1;
    while (hasTraceName(format.arg(i))) {
        i++;
    }
    return format.arg(i);
}
void IntermodTraceModel::fixTrace(int row) {
    bool isFixed = false;
    IntermodTrace &trace = _traces[row];
    if (!trace.isNameValid()) {
        trace.setName(QString("Trc%1").arg(row));
        isFixed = true;
    }
    if (!trace.isYValid()) {
        trace.setY(trace.possibleYParameters().first());
        isFixed = true;
    }
    if (!trace.isXValid()) {
        trace.setX(trace.possibleXParameters().first());
        isFixed = true;
    }
    if (!trace.isAtValid()) {
        trace.setAt(trace.possibleAtParameters().first());
        isFixed = true;
    }
    if (trace.isAtValue()) {
        QRowVector acceptableValues;
        if (trace.at() == "Center Frequency") {
            acceptableValues = _settings.centerFrequencies_Hz();
        }
        else if (trace.at() == "Tone Distance") {
            acceptableValues = _settings.toneDistances_Hz();
        }
        const double atValue = findClosest(trace.atValue(), acceptableValues);
        trace.setAtValue(atValue);
        isFixed = true;
    }

    if (isFixed) {
        QModelIndex left  = index(row, IntermodTraceModel::Column::name);
        QModelIndex right = index(row, IntermodTraceModel::Column::atValue);
        emit dataChanged(left, right);
    }
}
void IntermodTraceModel::fixTraces() {
    for (int i = 0; i < _traces.size(); i++) {
        fixTrace(i);
    }
}
