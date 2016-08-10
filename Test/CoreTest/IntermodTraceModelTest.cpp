#include "IntermodTraceModelTest.h"


// Project
//

// RsaToolbox
using namespace RsaToolbox;

// Qt
#include <QList>
#include <QSignalSpy>


typedef QList<IntermodTrace> Traces;


IntermodTraceModelTest::IntermodTraceModelTest(QObject *parent) :
    TestClass(parent)
{

}

IntermodTraceModelTest::~IntermodTraceModelTest()
{

}

void IntermodTraceModelTest::get_data() {
    QTest::addColumn<Traces>("traces");

    typedef TraceType Type;
    typedef TraceFeature Feature;

    // Empty
    Traces traces;
    QTest::newRow("Empty") << traces;

    // lti
    traces << IntermodTrace(Type::inputTone, Feature::lower);
    QTest::newRow("lti")   << traces;

    // ip3lo, ip5uo
    traces.clear();
    traces << IntermodTrace(Type::outputIntercept, Feature::lower, 3);
    traces << IntermodTrace(Type::outputIntercept, Feature::upper, 5);
    QTest::newRow("ip3loAndip5uo") << traces;
}
void IntermodTraceModelTest::get() {
    QFETCH(Traces, traces);

    IntermodTraceModel model;
    model.setTraces(traces);

    QCOMPARE(traces,        model.traces());
    QCOMPARE(traces.size(), model.rowCount());
    QCOMPARE(int(3)       , model.columnCount());

    for (int i = 0; i < traces.size(); i++) {
        // Qt::DisplayRole
        const IntermodTrace t = traces[i];
        QCOMPARE(toString(t.type())   , getDisplay(model, i, 0));
        QCOMPARE(toString(t.feature()), getDisplay(model, i, 1));
        if (t.hasOrder())
            QCOMPARE(t.order(), getDisplay(model, i, 2).toUInt());
        else
            QCOMPARE(QString(), getDisplay(model, i, 2));

        // Qt::EditRole
        QCOMPARE(getType(model, i)     , t.type());
        QCOMPARE(getFeature(model, i)  , t.feature());
        if (t.hasOrder())
            QCOMPARE(getOrder(model, i), t.order());
    }
}

void IntermodTraceModelTest::set_data() {
    QTest::addColumn<Traces>("traces");

    typedef TraceType Type;
    typedef TraceFeature Feature;

    // Empty
    Traces traces;
    QTest::newRow("Empty") << traces;

    // lti
    traces << IntermodTrace(Type::inputTone, Feature::lower);
    QTest::newRow("lti")   << traces;

    // im7mo
    traces.clear();
    traces << IntermodTrace(Type::intermod, Feature::major, 7);
    QTest::newRow("im7mo") << traces;

    // ip3lo, ip5uo
    traces.clear();
    traces << IntermodTrace(Type::outputIntercept, Feature::lower, 3);
    traces << IntermodTrace(Type::outputIntercept, Feature::upper, 5);
    QTest::newRow("ip3loAndip5uo") << traces;
}
void IntermodTraceModelTest::set() {
    QFETCH(Traces, traces);

    IntermodTraceModel model;
    model.insertRows(0, traces.size());
    QCOMPARE(traces.size(), model.rowCount());

    QSignalSpy dataChanged(&model, SIGNAL(dataChanged(QModelIndex,QModelIndex)));
    for (int i = 0; i < traces.size(); i++) {
        const IntermodTrace t = traces[i];

        // Type
        dataChanged.clear();
        QVERIFY(setType(model, i, t.type()));
        QVERIFY(dataChanged.count() == 1);
        QCOMPARE(t.type(), getType(model, i));

        // Feature
        dataChanged.clear();
        QVERIFY(setFeature(model, i, t.feature()));
        QVERIFY(dataChanged.count() == 1);
        QCOMPARE(t.feature(), getFeature(model, i));

        // Order
        dataChanged.clear();
        if (t.hasOrder()) {
            QVERIFY(setOrder(model, i, t.order()));
            QVERIFY(dataChanged.count() == 1);
            QCOMPARE(t.order(), getOrder(model, i));
        }
    }
    QCOMPARE(traces, model.traces());
}

QString IntermodTraceModelTest::getDisplay(IntermodTraceModel &model, int row, int column) {
    QModelIndex index = model.index(row, column);
    return model.data(index).toString();
}
TraceType IntermodTraceModelTest::getType(IntermodTraceModel &model, int row) {
    QModelIndex index = model.index(row, 0);
    QVariant v = model.data(index, Qt::EditRole);
    return   v.value<TraceType>();
}
TraceFeature IntermodTraceModelTest::getFeature(IntermodTraceModel &model, int row) {
    QModelIndex index = model.index(row, 1);
    QVariant v = model.data(index, Qt::EditRole);
    return   v.value<TraceFeature>();
}
uint IntermodTraceModelTest::getOrder(IntermodTraceModel &model, int row) {
    QModelIndex index = model.index(row, 2);
    QVariant v = model.data(index, Qt::EditRole);
    return   v.toUInt();
}

bool IntermodTraceModelTest::setType(IntermodTraceModel &model, int row, TraceType type) {
    QModelIndex index = model.index(row, 0);
    return model.setData(index, QVariant::fromValue(type));
}
bool IntermodTraceModelTest::setFeature(IntermodTraceModel &model, int row, TraceFeature feature) {
    QModelIndex index = model.index(row, 1);
    return model.setData(index, QVariant::fromValue(feature));
}
bool IntermodTraceModelTest::setOrder(IntermodTraceModel &model, int row, uint order) {
    QModelIndex index = model.index(row, 2);
    return model.setData(index, QVariant::fromValue(order));
}
