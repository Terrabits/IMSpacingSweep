#include "IntermodTraceDelegateTest.h"


// Project
#include "IntermodTraceDelegate.h"
#include "IntermodTraceModel.h"

// RsaToolbox
#include <Definitions.h>
#include <FrequencyEdit.h>
using namespace RsaToolbox;

// Qt
#include <QComboBox>
#include <QLineEdit>
#include <QSignalSpy>
#include <QStyleOptionViewItem>
#include <QWidget>


IntermodTraceDelegateTest::IntermodTraceDelegateTest(QObject *parent) :
    TestClass(parent)
{

}

IntermodTraceDelegateTest::~IntermodTraceDelegateTest()
{

}

void IntermodTraceDelegateTest::name() {
    IntermodSettings settings = defaultSettings();

    IntermodTraceDelegate delegate;
    delegate.setIntermodSettings(settings);

    IntermodTraceModel model;
    model.setSettings(settings);

    QList<IntermodTrace> traces;
    IntermodTrace trace;
    const QString name = "MyTrace";
    trace.setName   (name                );
    trace.setY      ("IM3 Upper"         );
    trace.setX      ("Center Frequency"  );
    trace.setAt     ("Tone Distance"     );
    trace.setAtValue(40.0, SiPrefix::Mega);
    traces << trace;
    model.setTraces(traces);

    const QModelIndex i
            = model.index(0, IntermodTraceModel::Column::name);
    QWidget *widget
            = delegate.createEditor(0,
                                    QStyleOptionViewItem(),
                                    i);
    QLineEdit *edit = qobject_cast<QLineEdit*>(widget);
    QVERIFY(edit);
    QVERIFY(edit->validator());

    delegate.setEditorData(widget, i);
    QCOMPARE(edit->text(), name);

    const QString newName = "MyNextTrace";
    edit->setText(newName);

    delegate.setModelData(widget, &model, i);
    QCOMPARE(model.data(i).toString(), newName);
}
void IntermodTraceDelegateTest::y() {
    IntermodSettings settings = defaultSettings();

    IntermodTraceDelegate delegate;
    delegate.setIntermodSettings(settings);

    IntermodTraceModel model;
    model.setSettings(settings);

    QList<IntermodTrace> traces;
    IntermodTrace trace;
    const QString y = "IM3 Upper";
    trace.setName   ("Trc1"              );
    trace.setY      (y                   );
    trace.setX      ("Center Frequency"  );
    trace.setAt     ("Tone Distance"     );
    trace.setAtValue(40.0, SiPrefix::Mega);
    traces << trace;
    model.setTraces(traces);

    const QModelIndex i
            = model.index(0, IntermodTraceModel::Column::y);
    QWidget *widget
            = delegate.createEditor(0,
                                    QStyleOptionViewItem(),
                                    i);
    QComboBox *combo = qobject_cast<QComboBox*>(widget);
    QVERIFY(combo);
    QVERIFY (!combo->isEditable());
    QCOMPARE(combo->count(), trace.possibleYParameters().size());

    delegate.setEditorData(widget, i);
    QCOMPARE(combo->currentText(), y);

    const QString newY = "IM5 Lower";
    combo->setCurrentText(newY);

    delegate.setModelData(widget, &model, i);
    QCOMPARE(model.data(i).toString(), newY);
}
void IntermodTraceDelegateTest::x() {
    IntermodSettings settings = defaultSettings();

    IntermodTraceDelegate delegate;
    delegate.setIntermodSettings(settings);

    IntermodTraceModel model;
    model.setSettings(settings);

    QList<IntermodTrace> traces;
    IntermodTrace trace;
    const QString x = "Center Frequency";
    trace.setName   ("Trc1"              );
    trace.setY      ("IM3 Upper"         );
    trace.setX      (x                   );
    trace.setAt     ("Tone Distance"     );
    trace.setAtValue(40.0, SiPrefix::Mega);
    traces << trace;
    model.setTraces(traces);

    const QModelIndex i
            = model.index(0, IntermodTraceModel::Column::x);
    QWidget *widget
            = delegate.createEditor(0,
                                    QStyleOptionViewItem(),
                                    i);
    QComboBox *combo = qobject_cast<QComboBox*>(widget);
    QVERIFY(combo);
    QVERIFY (!combo->isEditable());
    QCOMPARE(combo->count(), trace.possibleXParameters().size());

    delegate.setEditorData(widget, i);
    QCOMPARE(combo->currentText(), x);

    const QString newX = "Tone Distance";
    combo->setCurrentText(newX);

    delegate.setModelData(widget, &model, i);
    QCOMPARE(model.data(i).toString(), newX);
}
void IntermodTraceDelegateTest::at() {
    IntermodSettings settings = defaultSettings();

    IntermodTraceDelegate delegate;
    delegate.setIntermodSettings(settings);

    IntermodTraceModel model;
    model.setSettings(settings);

    QList<IntermodTrace> traces;
    IntermodTrace trace;
    const QString at = "Tone Distance";
    trace.setName   ("Trc1"              );
    trace.setY      ("IM3 Upper"         );
    trace.setX      ("Center Frequency"  );
    trace.setAt     (at                  );
    trace.setAtValue(40.0, SiPrefix::Mega);
    traces << trace;
    model.setTraces(traces);

    const QModelIndex i
            = model.index(0, IntermodTraceModel::Column::at);
    QWidget *widget
            = delegate.createEditor(0,
                                    QStyleOptionViewItem(),
                                    i);
    QComboBox *combo = qobject_cast<QComboBox*>(widget);
    QVERIFY (combo);
    QVERIFY (!combo->isEditable());
    QCOMPARE(combo->count(), trace.possibleAtParameters().size());

    delegate.setEditorData(widget, i);
    QCOMPARE(combo->currentText(), at);
}
void IntermodTraceDelegateTest::atValue() {
    IntermodSettings settings = defaultSettings();

    IntermodTraceDelegate delegate;
    delegate.setIntermodSettings(settings);

    IntermodTraceModel model;
    model.setSettings(settings);

    QList<IntermodTrace> traces;
    IntermodTrace trace;
    const double atValue = 40.0E6;
    trace.setName   ("Trc1"              );
    trace.setY      ("IM3 Upper"         );
    trace.setX      ("Center Frequency"  );
    trace.setAt     ("Tone Distance"     );
    trace.setAtValue(atValue);
    traces << trace;
    model.setTraces(traces);

    const QModelIndex i
            = model.index(0, IntermodTraceModel::Column::atValue);
    QWidget *widget
            = delegate.createEditor(0,
                                    QStyleOptionViewItem(),
                                    i);
    FrequencyEdit *edit = qobject_cast<FrequencyEdit*>(widget);
    QVERIFY(edit);

    delegate.setEditorData(widget, i);
    QCOMPARE(edit->frequency_Hz(), atValue);

    const double newAtValue = 50.0E6;
    edit->setFrequency(newAtValue);

    delegate.setModelData(widget, &model, i);
    QCOMPARE(model.data(i, Qt::EditRole).toDouble(), newAtValue);
}

IntermodSettings IntermodTraceDelegateTest::defaultSettings() {
    // Settings
    VnaIntermod::ToneSource port3;
    port3.setPort(3);

    IntermodSettings settings;
    settings.setLowerSourcePort(1);
    settings.setUpperSource    (port3);
    settings.setReceivingPort  (2);
    settings.setStartCenterFrequency (1, SiPrefix::Giga);
    settings.setStopCenterFrequency  (2, SiPrefix::Giga);
    settings.setCenterFrequencyPoints(11);
    settings.setStartToneDistance (10,  SiPrefix::Mega);
    settings.setStopToneDistance  (100, SiPrefix::Mega);
    settings.setToneDistancePoints(10);
    settings.setPower(-10);
    settings.setIfBw(  10, SiPrefix::Kilo);
    settings.setSelectivity(VnaChannel::IfSelectivity::High);
    return settings;
}
