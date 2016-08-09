#ifndef INTERMODERROR_H
#define INTERMODERROR_H


// Qt
#include <QString>


struct IntermodError {
    enum /*class*/ Code {
        LowerSourcePort,
        UpperSource,
        ReceivingPort,
        CenterFrequency,
        StartToneDistance,
        StopToneDistance,
        Points,
        Power,
        IfBw,
        Selectivity,
        Traces,
        Order,
        Channel,
        None
    };

    IntermodError();
    ~IntermodError();

    bool    isError() const;
    void    clear();

    Code    code;
    int     row;
    QString message;
};


#endif // INTERMODERROR_H
