#ifndef MEASURE_H
#define MEASURE_H


// Project
#include "Measurement.h"

//Qt
#include <QList>
#include <QThread>


class Measure : public QThread
{
    Q_OBJECT
public:
    Measure(QObject *parent = 0);

    void addMeasurement(Measurement *measurement);

signals:
    void starting();
    void progress(uint percent);
    void finished();

protected:
    virtual void run();

private slots:
    void incrementProgress(uint value);

private:
    QList<Measurement*> _measurements;
    uint _progress;
    uint _progressFactor;

    void connectMeasurement(Measurement *m);
    void disconnectMeasurement(Measurement *m);
};

#endif // MEASURE_H
