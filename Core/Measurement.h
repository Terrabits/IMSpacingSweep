#ifndef MEASUREMENT_H
#define MEASUREMENT_H


// Qt
#include <QObject>


class Measurement : public QObject
{
    Q_OBJECT

signals:
    void starting();
    void progress(uint percent);
    void finished();

public slots:
    virtual void run() = 0;
};

#endif // MEASUREMENT_H
