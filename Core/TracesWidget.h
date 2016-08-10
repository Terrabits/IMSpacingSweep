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
#include <Keys.h>
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
    explicit TracesWidget(RsaToolbox::Vna *vna, RsaToolbox::Keys *keys, QWidget *parent = 0);
    ~TracesWidget();

    bool isEmpty() const;
    bool isValidInput(IntermodError &error) const;
    IntermodTraces input() const;
    void setInput(const IntermodTraces &input);

    // Enter, leave
    virtual void initialize();
    virtual bool isReadyForNext();

signals:
    void error(const IntermodError &error);
    void errorMessage(const QString &message);

    void validatedInput(const IntermodTraces &input);

public slots:
    void setSettings(const IntermodSettings &settings);

    void saveInput();

    void showError(const IntermodError &error);
    void showErrorMessage(const QString &message);

private slots:
    void addTrace();
    void deleteTrace();
    void moveTraceUp();
    void moveTraceDown();

private:
    Ui::TracesWidget        *ui;
    mutable RsaToolbox::Vna *_vna;
    RsaToolbox::Keys        *_keys;
    IntermodSettings         _settings;
    bool                     _keysLoaded;

    IntermodTraceModel    _model;
    IntermodTraceDelegate _delegate;
    bool owns(const IntermodError &error) const;
    void setupMvc();
    void connectWidgets();

    void loadKeys();
    void saveKeys();
};

#endif // TRACESWIDGET_H
