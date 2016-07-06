#include "TraceSettings.h"


// Qt
#include <QRegExp>


TraceSettings::TraceSettings() :
    _atValue(0)
{

}
TraceSettings::~TraceSettings()
{

}
bool TraceSettings::isValid() const {
    if (!isNameValid())
        return false;
    if (!isYValid())
        return false;
    if (!isXValid())
        return false;
    if (!isAtValid())
        return false;
    // Else
    return true;
}
bool TraceSettings::isYValid() const {
    return possibleYParameters().contains(y());
}
bool TraceSettings::isXValid() const {
    return possibleXParameters().contains(x());
}
bool TraceSettings::isAtValid() const {
    return possibleAtParameters().contains(at());
}

bool TraceSettings::isNameValid() const {
    QRegExp regex("^[a-z_][0-9a-z_]*$", Qt::CaseInsensitive);
    return  regex.exactMatch(_name);
}
QString TraceSettings::name() const {
    return _name;
}
QString TraceSettings::y() const {
    return _y;
}
QString TraceSettings::x() const {
    return _x;
}
QString TraceSettings::at() const {
    return _at;
}
double TraceSettings::atValue() const {
    return _atValue;
}

void TraceSettings::setName(const QString &name) {
    _name = name;
}
void TraceSettings::setY(const QString &y) {
    _y = y;
}
void TraceSettings::setX(const QString &x) {
    _x = x;
}
void TraceSettings::setAt(const QString &at) {
    _at = at;
}
void TraceSettings::setAtValue(double value) {
    _atValue = value;
}

bool operator==(const TraceSettings &lhs, const TraceSettings &rhs) {
    if (lhs.name() != rhs.name())
        return false;
    if (lhs.y()    != rhs.y())
        return false;
    if (lhs.x()    != rhs.x())
        return false;
    if (lhs.isAt() && lhs.at()   != rhs.at())
        return false;
    if (lhs.isAtValue() && lhs.atValue() != rhs.atValue())
        return false;

    // Else
    return true;
}

    // How to implement?
//QDataStream &operator<<(QDataStream &stream, const TraceSettings &ts) {

//}
//QDataStream &operator>>(QDataStream &stream, TraceSettings &ts) {

//}
