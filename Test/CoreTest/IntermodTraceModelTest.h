#ifndef INTERMODTRACEMODELTEST_H
#define INTERMODTRACEMODELTEST_H


// Project
#include "IntermodTrace.h"
#include "IntermodTraceModel.h"

// RsaToolbox
#include <TestClass.h>

// Qt
#include <QObject>


class IntermodTraceModelTest : public RsaToolbox::TestClass
{
    Q_OBJECT
public:
    explicit IntermodTraceModelTest(QObject *parent = 0);
    ~IntermodTraceModelTest();

private slots:
    void get_data();
    void get     ();

    void set_data();
    void set     ();

private:
    QString      getDisplay(IntermodTraceModel &model, int row, int column);
    TraceType    getType   (IntermodTraceModel &model, int row);
    TraceFeature getFeature(IntermodTraceModel &model, int row);
    uint         getOrder  (IntermodTraceModel &model, int row);

    bool setType   (IntermodTraceModel &model, int row, TraceType type);
    bool setFeature(IntermodTraceModel &model, int row, TraceFeature feature);
    bool setOrder  (IntermodTraceModel &model, int row, uint order);

};

#endif // INTERMODTRACEMODELTEST_H
