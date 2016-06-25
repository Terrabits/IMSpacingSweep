#ifndef INTERMODWIDGET_H
#define INTERMODWIDGET_H

#include <QWidget>

namespace Ui {
class IntermodWidget;
}

class IntermodWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IntermodWidget(QWidget *parent = 0);
    ~IntermodWidget();

private:
    Ui::IntermodWidget *ui;
};

#endif // INTERMODWIDGET_H
