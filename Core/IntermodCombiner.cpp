#include "IntermodCombiner.h"


QString IntermodCombiner::toString(At at) {
    if (at == At::External)
        return "External";
    else
        return "Port";
}
IntermodCombiner::At IntermodCombiner::toAt(QString text) {
    text = text.toLower();
    if (text == "external")
        return At::External;
    else if (text == "port")
        return At::Port;
    else
        // default
        return At::External;
}

IntermodCombiner::IntermodCombiner() :
    _at  (At::External),
    _port(0)
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

bool operator==(const IntermodCombiner &left, const IntermodCombiner &right) {
    if (left.at() != right.at())
        return false;

    if (left.isPort()) {
        if (left.port() != right.port())
            return false;
    }

    // Else
    return true;
}
