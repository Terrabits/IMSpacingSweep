#ifndef INTERMODTRACE_H
#define INTERMODTRACE_H


// Project
#include "IntermodSettings.h"
#include "TraceSettings.h"

// RsaToolbox
#include <Definitions.h>

// Qt
#include <QLabel>
#include <QRegExp>
#include <QSharedPointer>


class IntermodTrace;
typedef QSharedPointer<IntermodTrace> SharedIntermodTrace;
typedef QList<SharedIntermodTrace> SharedIntermodTraces;

class IntermodTrace : public TraceSettings
{
public:
    static const QRegExp NAME_REGEX;

    IntermodTrace();
   ~IntermodTrace();

    bool isAtDistance() const;
    bool isAtCenter()   const;
    uint order() const;

    virtual bool        isAt()          const;
    virtual bool        isAtValue()     const;
    virtual QStringList possibleYParameters()  const;
    virtual QStringList possibleXParameters()  const;
    virtual QStringList possibleAtParameters() const;
    RsaToolbox::QRowVector possibleAtValues(const IntermodSettings &settings) const;
    virtual RsaToolbox::Units atUnits() const;
//    virtual double      maxAtValue()    const;
//    virtual double      minAtValue()    const;
};

#endif // INTERMODTRACE_H
