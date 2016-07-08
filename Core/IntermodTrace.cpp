#include "IntermodTrace.h"

IntermodTrace::IntermodTrace()
{

}

IntermodTrace::~IntermodTrace()
{

}

uint IntermodTrace::order() const {
    if (!isYValid())
        return 0;

    if (y().contains("Tone", Qt::CaseInsensitive))
        return 1;
    if (y().contains("3"))
        return 3;
    if (y().contains("5"))
        return 5;
    if (y().contains("7"))
        return 7;
    if (y().contains("9"))
        return 9;

    // Error
    return 0;
}

bool IntermodTrace::isAt() const {
    return false;
}
bool IntermodTrace::isAtValue() const {
    return false;
}
QStringList IntermodTrace::possibleYParameters() const {
    QStringList p;
    p << "Lower Tone Input";
    p << "Lower Tone Output";
    p << "Upper Tone Input";
    p << "Upper Tone Output";
    p << "IM3 Upper";
    p << "IM3 Lower";
    p << "IM3 Major";
    p << "IM5 Upper";
    p << "IM5 Lower";
    p << "IM5 Major";
    p << "IM7 Upper";
    p << "IM7 Lower";
    p << "IM7 Major";
    p << "IM9 Upper";
    p << "IM9 Lower";
    p << "IM9 Major";
    p << "IP3 Major";
    p << "IP5 Major";
    p << "IP7 Major";
    p << "IP9 Major";
    return p;
}
QStringList IntermodTrace::possibleXParameters() const {
    QStringList p;
    p << "Center Frequency";
    p << "Tone Distance";
    return p;
}
QStringList IntermodTrace::possibleAtParameters() const {
    QStringList p;
    if (x() == "Center Frequency")
        p << "Tone Distance";
    if (x() == "Tone Distance")
        p << "Center Frequency";
    return p;
}
RsaToolbox::Units IntermodTrace::atUnits() const {
    return RsaToolbox::Units::Hertz;
}
//double IntermodTrace::maxAtValue() const {

//}
//double IntermodTrace::minAtValue() const {

//}

