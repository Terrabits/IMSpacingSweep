#ifndef PROCESSTRACESWIDGET_H
#define PROCESSTRACESWIDGET_H


// Project
#include "IntermodError.h"
#include "IntermodSettings.h"
#include "IntermodTrace.h"

// RsaToolbox
#include <Vna.h>
#include <WizardPage.h>

// Qt
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

    // Enter, leave
    virtual void initialize();
    virtual void back();

signals:
    void error(const IntermodError &error);
    void progress(uint percent);

public slots:
    void setSettings(const IntermodSettings &settings  );
    void setTraces  (const QList<IntermodTrace> &traces);

    void run();

private:
    Ui::ProcessTracesWidget *ui;
    RsaToolbox::Vna         *_vna;
    IntermodSettings         _settings;
    QList<IntermodTrace>     _traces;
};


#endif // PROCESSTRACESWIDGET_H
