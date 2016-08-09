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
    void accessors_data();
    void accessors     ();

    void constructors  ();

//    void isType_data   ();
//    void isType        ();

//    void isFeature_data();
//    void isFeature     ();

//    void isOrder_data  ();
//    void isOrder       ();

    void display       ();

    void comparison();
    void sort();
};

#endif // INTERMODTRACETEST_H
