#ifndef INTERMODWIDGET_H
#define INTERMODWIDGET_H


// Project
#include "IntermodMeasurement.h"
#include "IntermodSettings.h"

// RsaToolbox
#include <Vna.h>
#include <WizardPage.h>

// Qt
#include <QWidget>


namespace Ui {
class IntermodWidget;
}

class IntermodWidget : public RsaToolbox::WizardPage
{
    Q_OBJECT

public:
    explicit IntermodWidget(RsaToolbox::Vna *vna, QWidget *parent = 0);
    ~IntermodWidget();

    bool isInput(IntermodError &error) const;
    IntermodSettings getInput() const;
    void setInput(const IntermodSettings &settings);

    // WizardPage
    virtual bool isReadyForNext();

signals:
    void error(const IntermodError &error);
    void errorMessage(QString message);
    void validatedInput(const IntermodSettings &settings);

public slots:
    void showError(const IntermodError &error);
    void showErrorMessage(const QString &message);

private:
    Ui::IntermodWidget *ui;
    mutable RsaToolbox::Vna *_vna;

    void initialize();
    void connectWidgets();

    static bool isLocal(const IntermodError &error);
    void focusOn(const IntermodError &error);
};

#endif // INTERMODWIDGET_H
