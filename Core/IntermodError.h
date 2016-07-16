#ifndef INTERMODERROR_H
#define INTERMODERROR_H


// Qt
#include <QString>


struct IntermodError {
    enum /*class*/ Code {
        LowerSourcePort,
        UpperSource,
        ReceivingPort,
        StartCenterFreq,
        StopCenterFreq,
        CenterFreqPoints,
        StartToneDistance,
        StopToneDistance,
        ToneDistancePoints,
        Power,
        IfBw,
        Selectivity,
        Traces,
        Order,
        None
    };

    IntermodError();
    ~IntermodError();

    bool    isError() const;
    void    clear();

    Code    code;
    int     row;
    int     column;
    QString message;
};


#endif // INTERMODERROR_H
