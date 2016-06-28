#ifndef INTERMODWIDGETTEST_H
#define INTERMODWIDGETTEST_H


// RsaToolbox
#include <GenericBus.h>
#include <VnaTestClass.h>

// Qt
#include <QObject>


class IntermodWidgetTest : public RsaToolbox::VnaTestClass
{
    Q_OBJECT
public:
    explicit IntermodWidgetTest(RsaToolbox::ConnectionType type, const QString &address, QObject *parent = 0);

private slots:
    void show();

private:

};

#endif // INTERMODWIDGETTEST_H
