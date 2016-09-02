#ifndef UPPERSOURCEEDIT_H
#define UPPERSOURCEEDIT_H


// RsaToolbox
#include <VnaIntermod.h>

// Qt
#include <QWidget>

namespace Ui {
class UpperSourceEdit;
}

class UpperSourceEdit : public QWidget
{
    Q_OBJECT

public:
    explicit UpperSourceEdit(QWidget *parent = 0);
    ~UpperSourceEdit();

    bool isInput() const;
    void setValue(RsaToolbox::VnaIntermod::ToneSource source);
    RsaToolbox::VnaIntermod::ToneSource value() const;

    void setVnaPorts(uint numberOfPorts);
    void setGenerators(uint numberOfGenerators);
    void clearGenerators();

signals:
    void outOfRange(const QString &message);

public slots:
    void selectAll();

private slots:
    void on_type_currentIndexChanged(const QString &arg1);

private:
    Ui::UpperSourceEdit *ui;

    uint _ports;
    uint _generators;

    void selectPort();

    bool _isGenerators;
    void enableGenerator  ();
    void selectGenerator();

    bool isPort() const;
    uint port  () const;
    uint generator() const;
};

#endif // UPPERSOURCEEDIT_H
