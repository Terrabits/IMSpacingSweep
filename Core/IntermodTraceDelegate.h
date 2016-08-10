#ifndef INTERMODTRACEDELEGATE_H
#define INTERMODTRACEDELEGATE_H


// Project
#include "IntermodError.h"
#include "IntermodSettings.h"
#include "IntermodTrace.h"

// Qt
#include <QObject>
#include <QString>
#include <QStyledItemDelegate>


class IntermodTraceDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit IntermodTraceDelegate(QObject *parent = 0);
    ~IntermodTraceDelegate();

    // Delegation
    virtual QWidget *createEditor (QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual void     setEditorData(QWidget *editor, const QModelIndex &index) const;
    virtual void     setModelData (QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    virtual void     updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    // Valid data ranges
    void setIntermodSettings(const IntermodSettings &settings);

signals:
    void errorMessage(const QString &message);

public slots:

private:
    IntermodSettings _settings;

    static QWidget *createTypeEditor   (QWidget *parent);
    static QWidget *createFeatureEditor(QWidget *parent, const IntermodTrace &t);
    static QWidget *createOrderEditor  (QWidget *parent);
};

#endif // INTERMODTRACEDELEGATE_H
