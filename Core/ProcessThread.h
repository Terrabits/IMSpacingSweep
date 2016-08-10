#ifndef PROCESSTHREAD_H
#define PROCESSTHREAD_H


// Project
#include "IntermodSettings.h"
#include "IntermodTrace.h"

// RsaToolbox
#include <Vna.h>

// Qt
#include <QObject>
#include <QThread>

class ProcessThread : public QThread
{
    Q_OBJECT
public:
    explicit ProcessThread(const IntermodSettings &settings,
                           const IntermodTraces   &traces,
                           RsaToolbox::Vna        *vna);
    ~ProcessThread();

protected:
    virtual void run();

private:
    IntermodSettings _settings;
    IntermodTraces   _traces;
    RsaToolbox::Vna *_vna;
};

#endif // PROCESSTHREAD_H
