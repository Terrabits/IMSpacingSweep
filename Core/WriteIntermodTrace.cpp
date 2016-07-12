#include "WriteIntermodTrace.h"


// Project
#include "IntermodFunctions.h"

// RsaToolbox
using namespace RsaToolbox;

// Qt
#include <QDebug>


WriteIntermodTrace::WriteIntermodTrace(RsaToolbox::Vna *vna, IntermodTrace trace, uint diagram, IntermodData &data) :
    _vna(vna),
    _trace(trace),
    _diagram(diagram),
    _data(data)
{
    const QString name  = _trace.name();
    const QString _name = "_" + name;

    QString          scpi;
    QRowVector       x;
    ComplexRowVector y;
    values(x, y, scpi);

    // Channel
    const uint c = _vna->createChannel();
    configureChannelForIntermod(_vna, c, _data.settings());
    VnaChannel channel = _vna->channel(c);
    channel.setName(_name);

    VnaLinearSweep sweep = channel.linearSweep();
    sweep.setStart (x.first());
    sweep.setStop  (x.last() );
    sweep.setPoints(x.size() );

    // Data trace
    _vna->createTrace(_name, c);
    _vna->trace(_name).setParameter(scpi);

    // Memory trace
    _vna->trace(_name).toMemory(name);
    _vna->trace(name).write(y);

    // Set diagram
    _vna->trace(_name).setDiagram(diagram);
}
WriteIntermodTrace::~WriteIntermodTrace()
{
    //
}

void WriteIntermodTrace::values(QRowVector &x, ComplexRowVector &y, QString &scpi) {
    y.clear();
    x.clear();
    scpi.clear();

    // Y
    ComplexMatrix2D *yMatrix = 0;
    const QString yParam = _trace.y();
    // Tones
    if (yParam == "Lower In") {
        scpi = "LTI";
        yMatrix = &(_data.lowerToneAtInput);
    }
    else if (yParam == "Lower Out") {
        scpi = "LTO";
        yMatrix = &(_data.lowerToneAtOutput);
    }
    else if (yParam == "Upper In") {
        scpi = "UTI";
        yMatrix = &(_data.upperToneAtInput);
    }
    else if (yParam == "Upper Out") {
        scpi = "UTO";
        yMatrix = &(_data.upperToneAtOutput);
    }
    // IM3
    else if (yParam == "IM3 Lower") {
        scpi = "IM3LO";
        yMatrix = &(_data.intermod3Lower);
    }
    else if (yParam == "IM3 Upper") {
        scpi = "IM3UO";
        yMatrix = &(_data.intermod3Upper);
    }
    else if (yParam == "IM3 Major") {
        scpi = "IM3MO";
        yMatrix = &(_data.intermod3Major);
    }
    // IM5
    else if (yParam == "IM5 Lower") {
        scpi = "IM5LO";
        yMatrix = &(_data.intermod5Lower);
    }
    else if (yParam == "IM5 Upper") {
        scpi = "IM5UO";
        yMatrix = &(_data.intermod5Upper);
    }
    else if (yParam == "IM5 Major") {
        scpi = "IM5MO";
        yMatrix = &(_data.intermod5Major);
    }
    // IM7
    else if (yParam == "IM7 Lower") {
        scpi = "IM7LO";
        yMatrix = &(_data.intermod7Lower);
    }
    else if (yParam == "IM7 Upper") {
        scpi = "IM7UO";
        yMatrix = &(_data.intermod7Upper);
    }
    else if (yParam == "IM7 Major") {
        scpi = "IM7MO";
        yMatrix = &(_data.intermod7Major);
    }
    // IM9
    else if (yParam == "IM9 Lower") {
        scpi = "IM9LO";
        yMatrix = &(_data.intermod9Lower);
    }
    else if (yParam == "IM9 Upper") {
        scpi = "IM9UO";
        yMatrix = &(_data.intermod9Upper);
    }
    else if (yParam == "IM9 Major") {
        scpi = "IM9MO";
        yMatrix = &(_data.intermod9Major);
    }
    // IP
    else if (yParam == "IP3 Major") {
        scpi = "IP3MO";
        yMatrix = &(_data.intercept3Major);
    }
    else if (yParam == "IP5 Major") {
        scpi = "IP5MO";
        yMatrix = &(_data.intercept5Major);
    }
    else if (yParam == "IP7 Major") {
        scpi = "IP7MO";
        yMatrix = &(_data.intercept7Major);
    }
    else if (yParam == "IP9 Major") {
        scpi = "IP9MO";
        yMatrix = &(_data.intercept9Major);
    }
    // No y match
    else {
        return;
    }

    const QString xParam = _trace.x();
    int iAt = -1;
    if (xParam == "Center Frequency") {
        // at: Tone Distance
        x = _data.centerFrequencies_Hz();
        iAt = _data.distances_Hz().indexOf(_trace.atValue());
        if (iAt == -1) {
            // Invalid at value
            scpi.clear();
            x.clear();
            return;
        }
        y = (*yMatrix)[iAt];

    }
    else if (xParam == "Tone Distance") {
        // at: Center Frequency
        x = _data.distances_Hz();
        iAt = _data.centerFrequencies_Hz().indexOf(_trace.atValue());
        if (iAt == -1) {
            // Invalid at value
            scpi.clear();
            x.clear();
            return;
        }
        y = column(*yMatrix, iAt);
    }
    // No x match
    else {
        scpi.clear();
        return;
    }
}
