#include "IntermodWidget.h"
#include "ui_IntermodWidget.h"

IntermodWidget::IntermodWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IntermodWidget)
{
    ui->setupUi(this);
}

IntermodWidget::~IntermodWidget()
{
    delete ui;
}
