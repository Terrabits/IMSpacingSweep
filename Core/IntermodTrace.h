#ifndef INTERMODTRACE_H
#define INTERMODTRACE_H


// Project
#include "TraceSettings.h"

// Qt
#include <QLabel>
#include <QSharedPointer>

class IntermodTrace;
typedef QSharedPointer<IntermodTrace> SharedIntermodTrace;
typedef QList<SharedIntermodTrace> SharedIntermodTraces;

class IntermodTrace : public TraceSettings
{
public:
    IntermodTrace();
   ~IntermodTrace();

    uint order() const;

    virtual bool        isAt()          const;
    virtual bool        isAtValue()     const;
    virtual QStringList possibleYParameters()  const;
    virtual QStringList possibleXParameters()  const;
    virtual QStringList possibleAtParameters() const;
    virtual RsaToolbox::Units atUnits() const;
//    virtual double      maxAtValue()    const;
//    virtual double      minAtValue()    const;
};

#endif // INTERMODTRACE_H
