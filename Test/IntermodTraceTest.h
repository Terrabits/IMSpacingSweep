#ifndef INTERMODTRACETEST_H
#define INTERMODTRACETEST_H


// RsaToolbox
#include <TestClass.h>

// Qt
#include <QObject>
#include <QString>


class IntermodTraceTest : public RsaToolbox::TestClass
{
    Q_OBJECT
public:
    IntermodTraceTest(QObject *parent = 0);
   ~IntermodTraceTest();

private slots:
    void trace_data();
    void trace();
};

#endif // INTERMODTRACETEST_H
