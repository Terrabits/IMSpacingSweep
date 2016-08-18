#include "IntermodError.h"


QString IntermodError::toString(Code code) {
    switch (code) {
    case Code::LowerSourcePort:
        return "Lower Source";
    case Code::UpperSource:
        return "Upper Source";
    case Code::Combiner:
        return "Combiner";
    case Code::ReceivingPort:
        return "Receiving Port";
    case Code::CenterFrequency:
        return "Center Frequency";
    case Code::StartToneDistance:
        return "Start Tone";
    case Code::StopToneDistance:
        return "Stop Tone";
    case Code::Points:
        return "Points";
    case Code::Power:
        return "Power";
    case Code::IfBw:
        return "IF BW";
    case Code::Selectivity:
        return "Selectivity";
    case Code::Traces:
        return "Traces";
    case Code::Order:
        return "Order";
    case Code::Channel:
        return "Channel";
    case Code::None:
    default:
        return QString();
    }
}

IntermodError::IntermodError()
{
    clear();
}
IntermodError::~IntermodError()
{
    //
}

bool IntermodError::isError() const {
    return code != Code::None;
}
void IntermodError::clear() {
    code   = Code::None;
    message.clear();
}

QString IntermodError::display() const {
    if (!isError())
        return "No error";

    QString s = "%1: %2";
    s = s.arg(toString(code));
    s = s.arg(message);
    return s;
}
