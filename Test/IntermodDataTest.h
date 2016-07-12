#ifndef INTERMODDATATEST_H
#define INTERMODDATATEST_H


// RsaToolbox
#include <Definitions.h>
#include <TestClass.h>


class IntermodDataTest : public RsaToolbox::TestClass
{
    Q_OBJECT
public:
    IntermodDataTest(QObject *parent = 0);
   ~IntermodDataTest();

private slots:
    void empty();
    void constructAll();
    void onlyTo5thOrder();
    void columnFunction();

private:
    void testMatrix(const RsaToolbox::ComplexMatrix2D &matrix, uint rows, uint columns);
};

#endif // INTERMODDATATEST_H
