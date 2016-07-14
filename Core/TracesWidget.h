#ifndef TRACESWIDGET_H
#define TRACESWIDGET_H

#include <QWidget>

namespace Ui {
class TracesWidget;
}

class TracesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TracesWidget(QWidget *parent = 0);
    ~TracesWidget();

private:
    Ui::TracesWidget *ui;
};

#endif // TRACESWIDGET_H
