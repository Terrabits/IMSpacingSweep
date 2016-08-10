#include "IntermodTrace.h"


// RsaToolbox
using namespace RsaToolbox;

// Qt
#include <QVariant>

typedef QList<IntermodTrace> Traces;


QString toString(TraceType type) {
    switch (type) {
    case TraceType::inputTone:
        return "Input";
    case TraceType::outputTone:
        return "Output";
    case TraceType::intermod:
        return "Intermod";
    case TraceType::relative:
        return "Relative";
    case TraceType::outputIntercept:
        return "Output Intercept";
    case TraceType::inputIntercept:
        return "Input Intercept";
    default:
        return "Input";
    }
}
TraceType toTraceType(QString string) {
    string = string.toLower();
//  bool isInput     = string.contains("input"    );
    bool isOutput    = string.contains("output"   );
    bool isIntermod  = string.contains("intermod" );
    bool isRelative  = string.contains("relative" );
    bool isIntercept = string.contains("intercept");

    if (isIntermod)
        return TraceType::intermod;
    if (isRelative)
        return TraceType::relative;
    if (isIntercept) {
        if (isOutput)
            return TraceType::outputIntercept;
        else
            return TraceType::inputIntercept;
    }
    if (isOutput)
        return TraceType::outputTone;
    else
        return TraceType::inputTone; // Default

}
QString toString(TraceFeature feature) {
    switch (feature) {
    case TraceFeature::upper:
        return "Upper";
    case TraceFeature::lower:
        return "Lower";
    case TraceFeature::major:
        return "Major";
    default:
        return "Lower";
    }
}
TraceFeature toTraceFeature(QString string) {
    string = string.toLower();
    if (string.contains("upper"))
        return TraceFeature::upper;
    if (string.contains("major"))
        return TraceFeature::major;

    // Else
    return TraceFeature::lower;
}

//const QRegExp IntermodTrace::NAME_REGEX("^[a-z_][0-9a-z_]*$", Qt::CaseInsensitive);

IntermodTrace::IntermodTrace() :
    _type   (TraceType::inputTone),
    _feature(TraceFeature::lower      ),
    _order  (3 ),
    _isVisible(true)
{
    //
}
IntermodTrace::IntermodTrace(TraceType type,
                             TraceFeature feature,
                             uint order) :
    _type   (type   ),
    _feature(feature),
    _order  (order  ),
    _isVisible(true)
{

}
IntermodTrace::IntermodTrace(QString s) {
    _isVisible = true;

    s = s.toLower();

    // Type
    const QString input        = toString(TraceType::inputTone ).toLower();
    const QString output       = toString(TraceType::outputTone).toLower();
    const QString intermod     = toString(TraceType::intermod  ).toLower();
    const QString relative     = toString(TraceType::relative  ).toLower();
    const QString outIntercept = toString(TraceType::outputIntercept ).toLower();
    const QString inIntercept  = toString(TraceType::inputIntercept).toLower();

    if (s.contains(intermod)) {
        _type = TraceType::intermod;
    }
    else if (s.contains(relative)) {
        _type = TraceType::relative;
    }
    else if (s.contains(outIntercept)) {
        _type = TraceType::outputIntercept;
    }
    else if (s.contains(inIntercept)) {
        _type = TraceType::inputIntercept;
    }
    else if (s.contains(input)) {
        _type = TraceType::inputTone;
    }
    else if (s.contains(output)) {
        _type = TraceType::outputTone;
    }
    else {
        // default type
        _type = TraceType::inputTone;
    }

    // Feature
    const QString upper = toString(TraceFeature::upper).toLower();
    const QString lower = toString(TraceFeature::lower).toLower();
    const QString major = toString(TraceFeature::major).toLower();
    if      (s.contains(upper)) {
        _feature = TraceFeature::upper;
    }
    else if (s.contains(lower)) {
        _feature = TraceFeature::lower;
    }
    else if (s.contains(major)) {
        _feature = TraceFeature::major;
    }
    else {
        // default feature
        _feature = TraceFeature::lower;
    }

    // Order
    const QString third   = "3rd";
    const QString fifth   = "5th";
    const QString seventh = "7th";
    const QString ninth   = "9th";
    if      (s.contains(third  )) {
        _order = 3;
    }
    else if (s.contains(fifth  )) {
        _order = 5;
    }
    else if (s.contains(seventh)) {
        _order = 7;
    }
    else if (s.contains(ninth  )) {
        _order = 9;
    }
    else {
        // default
        const bool isTone = _type == TraceType::inputTone
                         || _type == TraceType::outputTone;
        if (isTone) {
            _order = 1;
        }
        else {
            _order = 3;
        }
    }
}

IntermodTrace::~IntermodTrace()
{
    //
}

// Visible
bool IntermodTrace::isVisible() const {
    return _isVisible;
}
void IntermodTrace::hide     () {
    _isVisible = false;
}
void IntermodTrace::show     () {
    _isVisible = true;
}
void IntermodTrace::setVisible(bool isVisible) {
    _isVisible = isVisible;
}

// Dependent calculation
bool IntermodTrace::isDependent() const {
    if (isRelative())
        return true;
    if (isIntercept())
        return true;
    if (isMajor())
        return true;

    return false;
}
Traces IntermodTrace::dependents() const {
    if (isIntermod())
        return intermodDependents ();
    if (isRelative())
        return relativeDependents ();
    if (isIntercept())
        return interceptDependents();

    // Else
    return Traces();
}

// isType
bool IntermodTrace::isInputTone() const {
    return _type == TraceType::inputTone;
}
bool IntermodTrace::isOutputTone() const {
    return _type == TraceType::outputTone;
}
bool IntermodTrace::isIntermod() const {
    return _type == TraceType::intermod;
}
bool IntermodTrace::isRelative() const {
    return _type == TraceType::relative;
}
bool IntermodTrace::isIntercept() const {
    return isOutputIntercept() || isInputIntercept();
}
bool IntermodTrace::isOutputIntercept() const {
    return _type == TraceType::outputIntercept;
}
bool IntermodTrace::isInputIntercept () const {
    return _type == TraceType::inputIntercept;
}

// isFeature
bool IntermodTrace::isLower() const {
    return _feature == TraceFeature::lower;
}
bool IntermodTrace::isUpper() const {
    return _feature == TraceFeature::upper;
}
bool IntermodTrace::isMajor() const {
    return _feature == TraceFeature::major;
}

// isOrder
bool IntermodTrace::hasOrder () const {
    if (isInputTone ())
        return false;
    if (isOutputTone())
        return false;

    // else:
    //   intermod
    //   relative intermod
    //   intercept
    return true;
}
bool IntermodTrace::isThird  () const {
    if (!hasOrder())
        return false;

    return _order == 3;
}
bool IntermodTrace::isFifth  () const {
    if (!hasOrder())
        return false;

    return _order == 5;
}
bool IntermodTrace::isSeventh() const {
    if (!hasOrder())
        return false;

    return _order == 7;
}
bool IntermodTrace::isNinth  () const {
    if (!hasOrder())
        return false;

    return _order == 9;
}

// get
TraceType    IntermodTrace::type   () const {
    return _type;
}
TraceFeature IntermodTrace::feature() const {
    return _feature;
}
uint IntermodTrace::order() const {
    if (isInputTone() || isOutputTone())
        return 1;

    return _order;
}

// set
void IntermodTrace::setType   (TraceType type)  {
    _type = type;
}
void IntermodTrace::setFeature(TraceFeature feature) {
    _feature = feature;
}
void IntermodTrace::setOrder  (uint n)          {
    if (n <  3)          // too low
        _order =  3;
    else if (n >  9)     // too high
        _order =  9;
    else if (n % 2 == 0) // even
        _order =  n - 1;
    else
        _order = n;      // valid
}

QString IntermodTrace::display()       const {
    QString result;
    switch (_type) {
    case TraceType::inputTone:
    case TraceType::outputTone:
        result = "%1 %2";
        result = result.arg(featureString());
        result = result.arg(typeString   ());
        return result;
    case TraceType::intermod:
    case TraceType::relative:
    case TraceType::outputIntercept:
    case TraceType::inputIntercept:
        result = "%1 %2 %3";
        result = result.arg(orderString  ());
        result = result.arg(featureString());
        result = result.arg(typeString   ());
        return result;
    default:
        return "Lower Input";
    }
}
QString IntermodTrace::abbreviate()    const {
    QString result;
    switch (_type) {
    case TraceType::inputTone:
        result = "%1ti";
        result = result.arg(abbreviateFeature());
        return result;
    case TraceType::outputTone:
        result = "%1to";
        result = result.arg(abbreviateFeature());
        return result;
    case TraceType::intermod:
        result = "im%1%2o";
        result = result.arg(_order);
        result = result.arg(abbreviateFeature());
        return result;
    case TraceType::relative:
        result = "im%1%2or";
        result = result.arg(_order);
        result = result.arg(abbreviateFeature());
        return result;
    case TraceType::inputIntercept:
        result = "ip%1%2i";
        result = result.arg(_order);
        result = result.arg(abbreviateFeature());
        return result;
    case TraceType::outputIntercept:
        result = "ip%1%2o";
        result = result.arg(_order);
        result = result.arg(abbreviateFeature());
        return result;
    default:
        return "lti";
    }
}

Traces IntermodTrace::intermodDependents() const {
    Traces t;
    if (!isMajor())
        return t;

    t << IntermodTrace(TraceType::intermod, TraceFeature::lower, _order);
    t << IntermodTrace(TraceType::intermod, TraceFeature::upper, _order);
    return t;
}
Traces IntermodTrace::relativeDependents() const {
    Traces t;
    t << IntermodTrace(TraceType::outputTone, TraceFeature::lower);
    if (isLower() || isMajor()) {
        t << IntermodTrace(TraceType::intermod, TraceFeature::lower, _order);
    }
    if (isUpper() || isMajor()) {
        t << IntermodTrace(TraceType::intermod, TraceFeature::upper, _order);
    }
    return t;
}
Traces IntermodTrace::interceptDependents() const {
    Traces t;
    t << IntermodTrace(TraceType::outputTone, TraceFeature::lower);
    if (isInputIntercept()) {
        t << IntermodTrace(TraceType::inputTone, TraceFeature::lower);
    }
    if (isLower() || isMajor()) {
        t << IntermodTrace(TraceType::intermod, TraceFeature::lower, _order);
    }
    if (isUpper() || isMajor()) {
        t << IntermodTrace(TraceType::intermod, TraceFeature::upper, _order);
    }
    return t;
}

QString IntermodTrace::typeString()    const {
    return toString(_type);
}
QString IntermodTrace::featureString() const {
    return toString(_feature);
}
QString IntermodTrace::orderString()   const {
    if (_order == 1)
        return "1st";
    if (_order == 2)
        return "2nd";
    if (_order == 3)
        return "3rd";

    return QString("%1th").arg(_order);
}

QString IntermodTrace::abbreviateFeature() const {
    switch (_feature) {
    case TraceFeature::lower:
        return "l";
    case TraceFeature::upper:
        return "u";
    case TraceFeature::major:
        return "m";
    default:
        return "l";
    }
}

// Stream operators
QDataStream &operator<<(QDataStream &stream, const IntermodTrace &trace) {
    stream << quint32(trace.type     ());
    stream << quint32(trace.feature  ());
    stream << quint32(trace.order    ());
    stream <<         trace.isVisible();
    return stream;
}
QDataStream &operator>>(QDataStream &stream, IntermodTrace &trace) {
    bool isVisible;
    quint32   type ,  feature ,  order;
    stream >> type >> feature >> order >> isVisible;
    trace.setType   (TraceType   (type   ));
    trace.setFeature(TraceFeature(feature));
    trace.setOrder  (order    );
    trace.setVisible(isVisible);
    return stream;
}

// Boolean operators
bool operator==(const IntermodTrace &left, const IntermodTrace &right) {
    // not equal?
    if (left.type() != right.type())
        return false;
    if (left.feature() != right.feature())
        return false;
    if (left.hasOrder()) {
        if (left.order() != right.order())
            return false;
    }

    // equal!
    return true;
}
bool operator!=(const IntermodTrace &left, const IntermodTrace &right) {
    return !(left == right);
}

// Sort
bool operator< (const IntermodTrace &left, const IntermodTrace &right) {
    if (left.type() < right.type())
        return true;
    if (left.type() != right.type())
        return false;

    // ... same type

    if (left.feature() < right.feature())
        return true;
    if (left.feature() != right.feature())
        return false;

    // .. same feature

    if (!left.hasOrder()) {
        // No more properties
        // to compare.
        // They are equal
        return false;
    }

    // last property to compare
    return left.order() < right.order();
}
bool operator<=(const IntermodTrace &left, const IntermodTrace &right) {
    return  (left < right) || (left == right);
}
bool operator> (const IntermodTrace &left, const IntermodTrace &right) {
    return !(left <= right);
}
bool operator>=(const IntermodTrace &left, const IntermodTrace &right) {
    return !(left <  right);
}
