#include "IntermodCombiner.h"

IntermodCombiner::IntermodCombiner()
{

}

IntermodCombiner::~IntermodCombiner()
{

}

bool IntermodCombiner::isExternal() const {
    return _at == At::External;
}
bool IntermodCombiner::isPort    () const {
    return _at == At::Port;
}

IntermodCombiner::At IntermodCombiner::at() const {
    return _at;
}
uint IntermodCombiner::port() const {
    if (isPort())
        return _port;
    else
        return 0;
}

void IntermodCombiner::setExternal() {
    _at = At::External;
}
void IntermodCombiner::setPort(uint physicalPort) {
    _at   = At::Port;
    _port = physicalPort;
}
