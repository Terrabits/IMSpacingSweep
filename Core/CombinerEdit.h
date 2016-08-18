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

    IntermodCombiner combiner() const;

public slots:
    void setCombiner(IntermodCombiner combiner);

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
