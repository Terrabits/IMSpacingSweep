#ifndef PROCESSINTERMODTRACE_H
#define PROCESSINTERMODTRACE_H


// Project
#include "IntermodData.h"
#include "IntermodTrace.h"

// RsaToolbox
#include <Definitions.h>
#include <Vna.h>

// Qt
#include <QString>

class WriteIntermodTrace {
public:
    WriteIntermodTrace(RsaToolbox::Vna *vna, IntermodTrace trace, uint diagram, IntermodData &data);
    ~WriteIntermodTrace();

private:
    RsaToolbox::Vna *_vna;
    IntermodTrace    _trace;
    uint             _diagram;
    IntermodData    &_data;

    void values(RsaToolbox::QRowVector &x, RsaToolbox::ComplexRowVector &y, QString &scpi);
};

#endif // PROCESSINTERMODTRACE_H
