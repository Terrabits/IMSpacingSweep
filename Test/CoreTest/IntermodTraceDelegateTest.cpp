#include "IntermodTraceDelegateTest.h"


// Project
#include "IntermodTrace.h"
#include "IntermodTraceDelegate.h"
#include "IntermodTraceModel.h"

// RsaToolbox
using namespace RsaToolbox;

// Qt
#include <QComboBox>
#include <QDebug>
#include <QList>
#include <QPersistentModelIndex>
#include <QSignalSpy>
#include <QString>
#include <QStyleOptionViewItem>
#include <QWidget>


typedef QList<IntermodTrace> Traces;
Q_DECLARE_METATYPE(Traces)

IntermodTraceDelegateTest::IntermodTraceDelegateTest(QObject *parent) :
    TestClass(parent)
{

}

IntermodTraceDelegateTest::~IntermodTraceDelegateTest()
{

}

void IntermodTraceDelegateTest::set_data() {
    QTest::addColumn<Traces >("before");
    QTest::addColumn<int    >("row"   );
    QTest::addColumn<int    >("column");
    QTest::addColumn<QString>("text"  );
    QTest::addColumn<Traces >("after" );

    // One trace
    // Change type
    Traces before;
    before << IntermodTrace(TraceType::intermod, TraceFeature::major, 3);
    int row      = 0;
    int column   = 0;
    Traces after = before;
    after[row].setType(TraceType::relative);
    QTest::newRow("OneTraceType") << before << row << column << "Relative" << after;

    // Three traces
    // Change type of middle
    before.clear();
    before << IntermodTrace(TraceType::intermod,       TraceFeature::major, 3);
    before << IntermodTrace(TraceType::relative,       TraceFeature::major, 5);
    before << IntermodTrace(TraceType::inputIntercept, TraceFeature::major, 7);
    row    = 1;
    column = 0;
    after  = before;
    after[row].setType(TraceType::outputTone);

    QTest::newRow("MiddleType") << before << row << column << "Output" << after;

    // First feature
    row    = 0;
    column = 1;
    after  = before;
    after[row].setFeature(TraceFeature::upper);
    QTest::newRow("MiddleFeature") << before << row << column << "Upper" << after;

    // Last order
    row    = 2;
    column = 2;
    after  = before;
    after[row].setOrder(9);
    QTest::newRow("LastOrder") << before << row << column << "9" << after;


}
void IntermodTraceDelegateTest::set() {
    QFETCH(Traces, before);
    QFETCH(int, row);
    QFETCH(int, column);
    QFETCH(QString, text);
    QFETCH(Traces, after);

    IntermodTraceModel model;
    model.setTraces(before);
    QCOMPARE(before, model.traces());

    IntermodTraceDelegate delegate;

    QPersistentModelIndex i = model.index(row, column);
    QStyleOptionViewItem style;
    QWidget *w = delegate.createEditor(NULL, style, i);
    QComboBox *combo = qobject_cast<QComboBox*>(w);
    QVERIFY(combo);

    delegate.setEditorData(w, i);

    combo->setCurrentText(text);
    QCOMPARE(text, combo->currentText());

    QSignalSpy dataChanged(&model, SIGNAL(dataChanged(QModelIndex,QModelIndex)));
    delegate.setModelData(w, &model, i);
    QVERIFY(dataChanged.count() == 1);
    QCOMPARE(after, model.traces());
    delete w;
}

