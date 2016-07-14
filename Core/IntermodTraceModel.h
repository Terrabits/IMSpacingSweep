#ifndef INTERMODTRACEMODEL_H
#define INTERMODTRACEMODEL_H


// Project
#include "IntermodError.h"
#include "IntermodTrace.h"

// Qt
#include <QAbstractTableModel>
#include <QObject>
#include <QVariant>


class IntermodTraceModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit IntermodTraceModel(QObject *parent = 0);
    ~IntermodTraceModel();

    // Structure
    enum /*class*/ Column {
        name,
        y,
        x,
        at,
        atValue
    };

    // Model
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex &child) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());


    // Value
    QList<IntermodTrace> traces() const;
    void setTraces(const QList<IntermodTrace> &traces);

signals:
    void error(const IntermodError &error);

public slots:

private:
    QList<IntermodTrace> _traces;
};

#endif // INTERMODTRACEMODEL_H
