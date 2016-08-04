#ifndef INTERMODWIDGETTEST_H
#define INTERMODWIDGETTEST_H


// Project
#include "IntermodError.h"

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
    void printError(const IntermodError &error) const;
};

#endif // INTERMODWIDGETTEST_H
