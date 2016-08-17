#ifndef INTERMODCOMBINER_H
#define INTERMODCOMBINER_H


// Qt
#include <Qt>


struct IntermodCombiner
{
public:

    enum /*class*/ At {
        External,
        Port
    };

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

#endif // INTERMODCOMBINER_H
