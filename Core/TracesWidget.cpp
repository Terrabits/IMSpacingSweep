#include "TracesWidget.h"
#include "ui_TracesWidget.h"

TracesWidget::TracesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TracesWidget)
{
    ui->setupUi(this);
}

TracesWidget::~TracesWidget()
{
    delete ui;
}
