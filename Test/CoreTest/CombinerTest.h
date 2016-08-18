#ifndef COMBINERTEST_H
#define COMBINERTEST_H


// RsaToolbox
#include <TestClass.h>

// Qt
#include <QObject>


class CombinerTest : public RsaToolbox::TestClass
{
    Q_OBJECT
public:
    explicit CombinerTest(QObject *parent = 0);
    ~CombinerTest();

private slots:
    void intermodCombiner();
    void atConversion();
    void combinerEdit();
};

#endif // COMBINERTEST_H
