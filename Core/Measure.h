#ifndef MEASURE_H
#define MEASURE_H


// Project
#include "Measurement.h"

// RsaToolbox
#include <Vna.h>
#include <VnaPauseSweeps.h>

// Qt
#include <QList>
#include <QThread>


class Measure : public QThread
{
    Q_OBJECT
public:
    Measure(RsaToolbox::Vna *vna, QObject *parent = 0);
    ~Measure();

    void addMeasurement(Measurement *measurement);

signals:
    void started();
    void progress(uint percent);
    void finished();

protected:
    virtual void run();

private slots:
    void incrementProgress(uint value);

private:
    RsaToolbox::Vna           *_vna;
    RsaToolbox::VnaPauseSweeps _pause;

    QList<Measurement*> _measurements;

    uint _progress;
    void connectMeasurement(Measurement *m);
    void disconnectMeasurement(Measurement *m);
};


#endif // MEASURE_H
