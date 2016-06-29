#ifndef INTERMODWIDGET_H
#define INTERMODWIDGET_H


// Project
#include "IntermodMeasurement.h"
#include "IntermodSettings.h"

// RsaToolbox
#include <Vna.h>

// Qt
#include <QWidget>


namespace Ui {
class IntermodWidget;
}

class IntermodWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IntermodWidget(RsaToolbox::Vna *vna, QWidget *parent = 0);
    ~IntermodWidget();

    void initialize();

    bool isInput(IntermodError &error) const;
    IntermodSettings getInput() const;
    void setInput(const IntermodSettings &settings);

signals:
    void errorMessage(QString message);

private:
    Ui::IntermodWidget *ui;
    RsaToolbox::Vna *_vna;

    void connectWidgets();
};

#endif // INTERMODWIDGET_H
