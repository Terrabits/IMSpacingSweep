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
    static QString toString(Code code);

    IntermodError();
    ~IntermodError();

    bool    isError() const;
    void    clear();

    Code    code;
    QString message;

    QString display() const;
};


#endif // INTERMODERROR_H
