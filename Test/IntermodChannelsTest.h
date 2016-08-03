#ifndef INTERMODCHANNELSTEST_H
#define INTERMODCHANNELSTEST_H


// RsaToolbox
#include <GenericBus.h>
#include <VnaTestClass.h>

// Qt
#include <QObject>
#include <QString>


class IntermodChannelsTest : public RsaToolbox::VnaTestClass
{
    Q_OBJECT
public:
    IntermodChannelsTest(RsaToolbox::ConnectionType type, const QString &address, QObject *parent = 0);
    ~IntermodChannelsTest();

private slots:
    void basic();
};

#endif // INTERMODCHANNELSTEST_H
