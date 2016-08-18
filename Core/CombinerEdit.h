#ifndef COMBINEREDIT_H
#define COMBINEREDIT_H


// Project
#include "IntermodCombiner.h"

// Qt
#include <QWidget>


namespace Ui {
class CombinerEdit;
}

class CombinerEdit : public QWidget
{
    Q_OBJECT

public:
    explicit CombinerEdit(QWidget *parent = 0);
    ~CombinerEdit();

    void setVnaPorts(uint numberOfPorts);

    bool isPortEnabled() const;
    bool isPortEmpty  () const;
    IntermodCombiner value() const;

public slots:
    void enablePort (bool isEnabled = true);
    void disablePort(bool isDisabled = true);
    void setPortFocus();

    void setValue(IntermodCombiner value);

signals:
    void outOfRange(const QString &message);

private slots:
    void on_at_currentIndexChanged(const QString &arg1);

private:
    Ui::CombinerEdit *ui;

    IntermodCombiner::At at  () const;
    uint                 port() const;
};

#endif // COMBINEREDIT_H
