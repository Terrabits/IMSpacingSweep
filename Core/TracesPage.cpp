#include "TracesPage.h"
#include "ui_TracesPage.h"


// RsaToolbox
using namespace RsaToolbox;


TracesPage::TracesPage(QWidget *parent) :
    WizardPage(parent),
    ui(new ::Ui::TracesPage)
{
    ui->setupUi(this);
}

TracesPage::~TracesPage()
{
    delete ui;
}
