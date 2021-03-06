#ifndef CALIBRATEWIDGET_H
#define CALIBRATEWIDGET_H


// Project
#include "IntermodSettings.h"
#include "IntermodTrace.h"
#include "ProcessTraces.h"

// RsaToolbox
#include <Vna.h>
#include <WizardPage.h>

// Qt
#include <QWidget>

namespace Ui {
class CalibrateWidget;
}

class CalibrateWidget : public RsaToolbox::WizardPage
{
    Q_OBJECT

public:
    explicit CalibrateWidget(RsaToolbox::Vna *vna, QWidget *parent = 0);
    ~CalibrateWidget();

    virtual void initialize();
    virtual void back();
    virtual int  next();

public slots:
    void setSettings(const IntermodSettings     &settings);
    void setTraces  (const IntermodTraces &traces  );

    void setupCalibration();

private:
    Ui::CalibrateWidget  *ui;
    RsaToolbox::Vna      *_vna;

    IntermodSettings      _settings;
    QList<IntermodTrace>  _traces;
};

#endif // CALIBRATEWIDGET_H
