#ifndef INTERMODERROR_H
#define INTERMODERROR_H


// Qt
#include <QString>


class IntermodError {
public:
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
    bool isError() const;
    Code code;
    QString message;
    void clear();
};

#endif // INTERMODERROR_H
