#ifndef INTERMODCOMBINER_H
#define INTERMODCOMBINER_H


// Qt
#include <Qt>
#include <QString>


struct IntermodCombiner
{
public:

    enum /*class*/ At {
        External,
        Port
    };
    static QString toString(At at);
    static At      toAt(QString text);

    IntermodCombiner();
    ~IntermodCombiner();

    bool isExternal() const;
    bool isPort    () const;

    At   at  () const;
    uint port() const;

    void setExternal();
    void setPort(uint physicalPort);

private:
    At   _at;
    uint _port;
};

bool operator==(const IntermodCombiner &left, const IntermodCombiner &right);

#endif // INTERMODCOMBINER_H
