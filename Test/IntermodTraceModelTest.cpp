#include "IntermodTraceModelTest.h"


// Project
#include "IntermodTraceModel.h"
#include "IntermodSettings.h"

// RsaToolbox
using namespace RsaToolbox;

// Qt
#include <QSignalSpy>


IntermodTraceModelTest::IntermodTraceModelTest(QObject *parent) : TestClass(parent)
{

}

IntermodTraceModelTest::~IntermodTraceModelTest()
{

}

void IntermodTraceModelTest::basic() {
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
    settings.setStartToneDistance (10, SiPrefix::Mega);
    settings.setStopToneDistance  (100, SiPrefix::Mega);
    settings.setToneDistancePoints(10);
    settings.setPower(-10);
    settings.setIfBw(  10, SiPrefix::Kilo);
    settings.setSelectivity(VnaChannel::IfSelectivity::High);

    IntermodTraceModel model;
    model.setSettings(settings);

    QCOMPARE(model.rowCount(), 0);

    QSignalSpy dataChanged          (&model, SIGNAL(dataChanged(QModelIndex,QModelIndex      )) );
    QSignalSpy rowsAboutToBeInserted(&model, SIGNAL(rowsAboutToBeInserted(QModelIndex,int,int)) );
    QSignalSpy rowsInserted         (&model, SIGNAL(rowsInserted(QModelIndex,int,int         )) );
    QSignalSpy rowsAboutToBeRemoved (&model, SIGNAL(rowsAboutToBeRemoved(QModelIndex,int,int )) );
    QSignalSpy rowsRemoved          (&model, SIGNAL(rowsRemoved(QModelIndex,int,int          )) );
    QSignalSpy modelAboutToBeReset  (&model, SIGNAL(modelAboutToBeReset(                     )) );
    QSignalSpy modelReset           (&model, SIGNAL(modelReset(                              )) );

    // New trace
    QVERIFY (model.appendNewTrace());
    QCOMPARE(model.rowCount(),              1);
    QCOMPARE(dataChanged.count(),           0);
    QCOMPARE(rowsAboutToBeInserted.count(), 1);
    QCOMPARE(rowsInserted.count(),          1);
    QCOMPARE(rowsAboutToBeRemoved.count(),  0);
    QCOMPARE(rowsRemoved.count(),           0);
    QCOMPARE(modelAboutToBeReset.count(),   0);
    QCOMPARE(modelReset.count(),            0);
    rowsAboutToBeInserted.clear();
    rowsInserted.clear();

    // New trace name
    QModelIndex i = model.index(0, IntermodTraceModel::Column::name);
    QCOMPARE(model.data(i).toString(), QString("Trc1"));

    // Set name
    i = model.index(0, IntermodTraceModel::Column::name);
    const QString name = "my_trace_name";
    QVERIFY (model.setData(i,            name));
    QCOMPARE(model.data(i).toString(),   name);
    QCOMPARE(dataChanged.count(),           1);
    QCOMPARE(rowsAboutToBeInserted.count(), 0);
    QCOMPARE(rowsInserted.count(),          0);
    QCOMPARE(rowsAboutToBeRemoved.count(),  0);
    QCOMPARE(rowsRemoved.count(),           0);
    QCOMPARE(modelAboutToBeReset.count(),   0);
    QCOMPARE(modelReset.count(),            0);
    dataChanged.clear();

    // Set Y
    i = model.index(0, IntermodTraceModel::Column::y);
    const QString y = "IM3 Upper";
    QVERIFY (model.setData(i,               y));
    QCOMPARE(model.data(i).toString(),      y);
    QCOMPARE(dataChanged.count(),           1);
    QCOMPARE(rowsAboutToBeInserted.count(), 0);
    QCOMPARE(rowsInserted.count(),          0);
    QCOMPARE(rowsAboutToBeRemoved.count(),  0);
    QCOMPARE(rowsRemoved.count(),           0);
    QCOMPARE(modelAboutToBeReset.count(),   0);
    QCOMPARE(modelReset.count(),            0);
    dataChanged.clear();

    // Set X
    i = model.index(0, IntermodTraceModel::Column::x);
    const QString x = "Tone Distance";
    QVERIFY (model.setData(i,               x));
    QCOMPARE(model.data(i).toString(),      x);
    QCOMPARE(dataChanged.count(),           1);
    QCOMPARE(rowsAboutToBeInserted.count(), 0);
    QCOMPARE(rowsInserted.count(),          0);
    QCOMPARE(rowsAboutToBeRemoved.count(),  0);
    QCOMPARE(rowsRemoved.count(),           0);
    QCOMPARE(modelAboutToBeReset.count(),   0);
    QCOMPARE(modelReset.count(),            0);
    dataChanged.clear();

    // Set at value
    i = model.index(0, IntermodTraceModel::Column::atValue);
    const double at = 1.4E9; // 1 GHz center freq
    QVERIFY (model.setData(i,                        at));
    QCOMPARE(model.data(i, Qt::EditRole).toDouble(), at);
    QCOMPARE(dataChanged.count(),           1);
    QCOMPARE(rowsAboutToBeInserted.count(), 0);
    QCOMPARE(rowsInserted.count(),          0);
    QCOMPARE(rowsAboutToBeRemoved.count(),  0);
    QCOMPARE(rowsRemoved.count(),           0);
    QCOMPARE(modelAboutToBeReset.count(),   0);
    QCOMPARE(modelReset.count(),            0);
    dataChanged.clear();

    // Delete trace
    QVERIFY (model.removeRow(0));
    QCOMPARE(model.rowCount(),              0);
    QCOMPARE(dataChanged.count(),           0);
    QCOMPARE(rowsAboutToBeInserted.count(), 0);
    QCOMPARE(rowsInserted.count(),          0);
    QCOMPARE(rowsAboutToBeRemoved.count(),  1);
    QCOMPARE(rowsRemoved.count(),           1);
    QCOMPARE(modelAboutToBeReset.count(),   0);
    QCOMPARE(modelReset.count(),            0);
    rowsAboutToBeRemoved.clear();
    rowsRemoved.clear();
}
void IntermodTraceModelTest::flags() {
    IntermodTraceModel model;
    model.appendNewTrace();

    QModelIndex i = model.index(0, IntermodTraceModel::Column::name);
    Qt::ItemFlags flags = model.flags(i);
    QVERIFY(flags & Qt::ItemIsEditable);
    QVERIFY(flags & Qt::ItemIsEnabled);
    QVERIFY(flags & Qt::ItemIsSelectable);

    i = model.index(0, IntermodTraceModel::Column::y);
    flags = model.flags(i);
    QVERIFY(flags & Qt::ItemIsEditable);
    QVERIFY(flags & Qt::ItemIsEnabled);
    QVERIFY(flags & Qt::ItemIsSelectable);

    i = model.index(0, IntermodTraceModel::Column::x);
    flags = model.flags(i);
    QVERIFY(flags & Qt::ItemIsEditable);
    QVERIFY(flags & Qt::ItemIsEnabled);
    QVERIFY(flags & Qt::ItemIsSelectable);

    i = model.index(0, IntermodTraceModel::Column::at);
    flags = model.flags(i);
    QVERIFY(!(flags & Qt::ItemIsEditable));
    QVERIFY(flags & Qt::ItemIsEnabled);
    QVERIFY(flags & Qt::ItemIsSelectable);

    i = model.index(0, IntermodTraceModel::Column::atValue);
    flags = model.flags(i);
    QVERIFY(flags & Qt::ItemIsEditable);
    QVERIFY(flags & Qt::ItemIsEnabled);
    QVERIFY(flags & Qt::ItemIsSelectable);
}
