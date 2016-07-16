#ifndef INTERMODTRACEMODELTEST_H
#define INTERMODTRACEMODELTEST_H


// RsaToolbox
#include <TestClass.h>

// Qt
#include <QObject>


class IntermodTraceModelTest : public RsaToolbox::TestClass
{
    Q_OBJECT
public:
    explicit IntermodTraceModelTest(QObject *parent = 0);
    ~IntermodTraceModelTest();

private slots:
    void basic();
    void flags();
};

#endif // INTERMODTRACEMODELTEST_H
