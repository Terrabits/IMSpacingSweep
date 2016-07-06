#ifndef INTERMODDATATEST_H
#define INTERMODDATATEST_H


// RsaToolbox
#include <TestClass.h>


class IntermodDataTest : public RsaToolbox::TestClass
{
    Q_OBJECT
public:
    IntermodDataTest(QObject *parent = 0);
   ~IntermodDataTest();

private slots:
    void size();
};

#endif // INTERMODDATATEST_H
