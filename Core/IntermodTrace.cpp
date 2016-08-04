#include "IntermodTrace.h"


// RsaToolbox
using namespace RsaToolbox;


const QRegExp IntermodTrace::NAME_REGEX("^[a-z_][0-9a-z_]*$", Qt::CaseInsensitive);

IntermodTrace::IntermodTrace()
{
    //
}

IntermodTrace::~IntermodTrace()
{
    //
}

bool IntermodTrace::isValid    () const {
    return isNameValid() && isYValid();
}
bool IntermodTrace::isNameValid() const {
    return NAME_REGEX.exactMatch(_name);
}
bool IntermodTrace::isYValid   () const {
    return possibleYParameters().contains(_y, Qt::CaseInsensitive);
}

bool IntermodTrace::isMajor    () const {
    return _y.contains("Major", Qt::CaseInsensitive);
}
bool IntermodTrace::isRelative () const {
    return false;
}
bool IntermodTrace::isIntercept() const {
    return _y.contains("IP", Qt::CaseInsensitive);
}
uint IntermodTrace::order      () const {
    if (!isYValid())
        return 0;

    if (_y.contains("Input", Qt::CaseInsensitive))
        return 1;
    if (_y.contains("Output"), Qt::CaseInsensitive)
        return 1;
    if (_y.contains("3"))
        return 3;
    if (_y.contains("5"))
        return 5;
    if (_y.contains("7"))
        return 7;
    if (_y.contains("9"))
        return 9;

    // Error
    return 0;
}

QStringList IntermodTrace::possibleYParameters() const {
    QStringList p;
    p << "Lower Input";
    p << "Lower Output";
    p << "Upper Input";
    p << "Upper Output";
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

QString IntermodTrace::name() const {
    return _name;
}
QString IntermodTrace::y   () const {
    return _y;
}
void IntermodTrace::setName(const QString &name) {
    _name = name;
}
void IntermodTrace::setY   (const QString &y   ) {
    _y    = y;
}
