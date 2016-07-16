#ifndef WRITEINTERMODTRACETEST_H
#define WRITEINTERMODTRACETEST_H


// RsaToolbox
#include <VnaTestClass.h>

// Qt
#include <QObject>

class WriteIntermodTraceTest : public RsaToolbox::VnaTestClass
{
    Q_OBJECT
public:
    explicit WriteIntermodTraceTest(RsaToolbox::ConnectionType type, const QString &address, QObject *parent = 0);
    ~WriteIntermodTraceTest();

private slots:
    void basic();

};

#endif // WRITEINTERMODTRACETEST_H
