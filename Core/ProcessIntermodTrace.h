#ifndef PROCESSINTERMODTRACE_H
#define PROCESSINTERMODTRACE_H


// Project
#include "IntermodData.h"
#include "IntermodTrace.h"

// RsaToolbox
#include <Vna.h>


void processIntermodTrace(RsaToolbox::Vna *vna, IntermodTrace trace, IntermodData &data);


#endif // PROCESSINTERMODTRACE_H
