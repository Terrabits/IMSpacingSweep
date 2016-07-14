#ifndef TRACESWIDGETTEST_H
#define TRACESWIDGETTEST_H


// RsaToolbox
#include <VnaTestClass.h>

// Qt
#include <QObject>


class TracesWidgetTest : public RsaToolbox::VnaTestClass
{
    Q_OBJECT
public:
    explicit TracesWidgetTest(RsaToolbox::ConnectionType type, const QString &address, QObject *parent = 0);
    ~TracesWidgetTest();

signals:

public slots:
};

#endif // TRACESWIDGETTEST_H
