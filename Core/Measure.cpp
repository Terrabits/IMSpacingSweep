#include "Measure.h"

Measure::Measure(RsaToolbox::Vna *vna, QObject *parent) :
    QThread(parent),
    _vna(vna),
    _pause(vna),
    _progress(0)
{
    //
}
Measure::~Measure()
{
    //
}

void Measure::addMeasurement(Measurement *measurement) {
    measurement->setParent(this);
    _measurements.append(measurement);
}

void Measure::incrementProgress(uint value) {
    _progress += uint(value / _measurements.size());
    emit progress(_progress);
}

void Measure::run() {
    emit started();
    emit progress(0);
    _progress = 0;
    foreach (Measurement *m, _measurements) {
        connectMeasurement(m);
        m->run();
        disconnectMeasurement(m);
    }
    emit progress(100);
    emit finished();
}

void Measure::connectMeasurement(Measurement *m) {
    connect(m, SIGNAL(progress(uint)),
            this, SLOT(incrementProgress(uint)));
}
void Measure::disconnectMeasurement(Measurement *m) {
    disconnect(m, SIGNAL(progress(uint)),
               this, SLOT(incrementProgress(uint)));
}
