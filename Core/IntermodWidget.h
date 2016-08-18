#ifndef INTERMODWIDGET_H
#define INTERMODWIDGET_H


// Project
#include "IntermodError.h"
#include "IntermodSettings.h"

// RsaToolbox
#include <Keys.h>
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
    explicit IntermodWidget(RsaToolbox::Vna *vna, RsaToolbox::Keys *keys = 0, QWidget *parent = 0);
    ~IntermodWidget();

    bool isValidInput(IntermodError &error) const;
    IntermodSettings input() const;
    void setInput(const IntermodSettings &settings);

    // Leave page
    virtual bool isReadyForNext();

signals:
    void error(const IntermodError &error);
    void errorMessage(const QString &message);
    void validatedInput(const IntermodSettings &settings);

public slots:
    void saveInput();

    void showError(const IntermodError &error);
    void showErrorMessage(const QString &message);

private:
    Ui::IntermodWidget      *ui;
    mutable RsaToolbox::Vna *_vna;
    RsaToolbox::Keys        *_keys;

    void setInputLimits();
    void connectWidgets();
    void loadKeys();
    void saveKeys();

    // Input
    RsaToolbox::VnaChannel::IfSelectivity selectivity() const;
    void setSelectivity(RsaToolbox::VnaChannel::IfSelectivity s);
    uint channel() const;
    void setChannel(uint index);

    static bool owns(const IntermodError &error);
    void focusOn(const IntermodError &error);
};

#endif // INTERMODWIDGET_H
