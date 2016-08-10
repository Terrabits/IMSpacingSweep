#ifndef PROCESSTRACESWIDGET_H
#define PROCESSTRACESWIDGET_H


// Project
#include "IntermodError.h"
#include "IntermodSettings.h"
#include "IntermodTrace.h"
#include "ProcessThread.h"

// RsaToolbox
#include <Vna.h>
#include <WizardPage.h>

// Qt
#include <QScopedPointer>
#include <QWidget>


namespace Ui {
class ProcessTracesWidget;
}

class ProcessTracesWidget : public RsaToolbox::WizardPage
{
    Q_OBJECT
public:
    explicit ProcessTracesWidget(RsaToolbox::Vna *vna, QWidget *parent = 0);
    ~ProcessTracesWidget();

    // On entry
    virtual void initialize();

public slots:
    void setSettings(const IntermodSettings &settings  );
    void setTraces  (const IntermodTraces &traces);

private slots:
    void processFinished();

private:
    Ui::ProcessTracesWidget *ui;
    RsaToolbox::Vna         *_vna;
    IntermodSettings         _settings;
    IntermodTraces           _traces;

    QScopedPointer<ProcessThread> _process;
};


#endif // PROCESSTRACESWIDGET_H
