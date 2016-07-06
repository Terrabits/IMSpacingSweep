#ifndef INTERMODTRACE_H
#define INTERMODTRACE_H


// Project
#include "TraceSettings.h"


class IntermodTrace : public TraceSettings
{
public:
    IntermodTrace();
   ~IntermodTrace();

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
