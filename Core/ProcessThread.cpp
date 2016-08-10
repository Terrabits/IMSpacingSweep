#include "ProcessThread.h"


// Project
#include "ProcessTraces.h"


ProcessThread::ProcessThread(const IntermodSettings &settings,
                             const IntermodTraces &traces,
                             RsaToolbox::Vna *vna) :
    _settings(settings),
    _traces(traces),
    _vna(vna)
{

}

ProcessThread::~ProcessThread()
{

}

void ProcessThread::run() {
    ProcessTraces p(_traces, _settings, _vna);
    p.run();
}
