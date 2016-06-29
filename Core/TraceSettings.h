#ifndef TRACESETTINGS_H
#define TRACESETTINGS_H


// RsaToolbox
#include <Definitions.h>

// Qt
#include <QDataStream>
#include <QString>
#include <QStringList>


class TraceSettings
{
public:
    TraceSettings();
    ~TraceSettings();

    bool isValid()   const;
    bool isYValid()  const;
    bool isXValid()  const;
    bool isAtValid() const;

    QString name()    const;
    QString y()       const;
    QString x()       const;
    QString at()      const;
    double  atValue() const;

    void setName(const QString &name);
    void setY   (const QString &y);
    void setX   (const QString &x);
    void setAt  (const QString &at);
    void setAtValue(double value);

    bool isAt()       const = 0;
    bool isAtValue()  const = 0;
    virtual QStringList possibleYParameters()  const = 0;
    virtual QStringList possibleXParameters()  const = 0;
    virtual QStringList possibleAtParameters() const = 0;
    RsaToolbox::Units   atUnits()    const = 0;
//    virtual double      maxAtValue() const = 0;
//    virtual double      minAtValue() const = 0;

private:
    QString _name;
    QString _y;
    QString _x;
    QString _at;
    double  _atValue;
};

bool operator==(const TraceSettings &lhs, const TraceSettings &rhs);
//QDataStream &operator<<(QDataStream &stream, const TraceSettings &ts);
//QDataStream &operator>>(QDataStream &stream, TraceSettings &ts);


#endif // TRACESETTINGS_H
