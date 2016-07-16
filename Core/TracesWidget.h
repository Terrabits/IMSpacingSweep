#ifndef TRACESWIDGET_H
#define TRACESWIDGET_H


// Project
#include "IntermodError.h"
#include "IntermodTrace.h"
#include "IntermodTraceDelegate.h"
#include "IntermodTraceModel.h"

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
    void initialize();
    void back();

signals:
    void error(const IntermodError &error);
    void errorMessage(const QString &message);

public slots:
    void addTrace();
    void deleteTrace();
    void moveTraceUp();
    void moveTraceDown();

    void showError(const IntermodError &error);
    void showErrorMessage(const QString &message);

    void measure();

private:
    Ui::TracesWidget *ui;
    mutable RsaToolbox::Vna *_vna;

    IntermodTraceModel    _model;
    IntermodTraceDelegate _delegate;
    bool owns(const IntermodError &error) const;
    void setupMvc();
    void connectWidgets();
};

#endif // TRACESWIDGET_H
