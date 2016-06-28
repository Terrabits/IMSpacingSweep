#ifndef INTERMODWIDGET_H
#define INTERMODWIDGET_H


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

private:
    Ui::IntermodWidget *ui;
    RsaToolbox::Vna *_vna;
};

#endif // INTERMODWIDGET_H
