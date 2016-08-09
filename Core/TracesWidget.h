#ifndef TRACESWIDGET_H
#define TRACESWIDGET_H


// Project
#include "IntermodError.h"
#include "IntermodSettings.h"
#include "IntermodTrace.h"
#include "IntermodTraceDelegate.h"
#include "IntermodTraceModel.h"
#include "ProcessTraces.h"

// RsaToolbox
#include <Vna.h>
#include <WizardPage.h>

// Qt
#include <QList>
#include <QString>
#include <QWidget>


namespace Ui {
class TracesWidget;
}

class TracesWidget : public RsaToolbox::WizardPage
{
    Q_OBJECT

public:
    explicit TracesWidget(RsaToolbox::Vna *vna, QWidget *parent = 0);
    ~TracesWidget();

    bool isEmpty() const;
    bool isValidInput(IntermodError &error) const;
    QList<IntermodTrace> traces() const;
    void setTraces(const QList<IntermodTrace> &traces);

    // Enter, leave
    virtual bool isReadyForNext();

signals:
    void error(const IntermodError &error);
    void errorMessage(const QString &message);

    void validatedInput(const QList<IntermodTrace> &traces);

public slots:
    void setSettings(const IntermodSettings &settings);

    void showError(const IntermodError &error);
    void showErrorMessage(const QString &message);

    void measure();

private slots:
    void addTrace();
    void deleteTrace();
    void moveTraceUp();
    void moveTraceDown();

private:
    Ui::TracesWidget *ui;
    mutable RsaToolbox::Vna *_vna;
    IntermodSettings         _settings;

    IntermodTraceModel    _model;
    IntermodTraceDelegate _delegate;
    bool owns(const IntermodError &error) const;
    void setupMvc();
    void connectWidgets();
};

#endif // TRACESWIDGET_H
