#ifndef TRACESPAGE_H
#define TRACESPAGE_H


// RsaToolbox
#include <WizardPage.h>

// Qt
#include <QWidget>


namespace Ui {
class TracesPage;
}

class TracesPage : public RsaToolbox::WizardPage
{
    Q_OBJECT

public:
    explicit TracesPage(QWidget *parent = 0);
    ~TracesPage();

private:
    Ui::TracesPage *ui;
};

#endif // TRACESPAGE_H
