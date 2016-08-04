#ifndef INTERMODTRACE_H
#define INTERMODTRACE_H


// RsaToolbox
#include <Definitions.h>

// Qt
#include <Qt>
#include <QLabel>
#include <QRegExp>
#include <QString>
#include <QStringList>


class IntermodTrace
{
public:
    static const QRegExp NAME_REGEX;

    IntermodTrace();
   virtual ~IntermodTrace();

    bool isValid() const;
    bool isNameValid() const;
    bool isYValid() const;

    bool isMajor() const;
    bool isRelative() const;
    bool isIntercept() const;
    uint order  () const;

    QStringList possibleYParameters()  const;

    QString name() const;
    QString y   () const;
    void    setName(const QString &name);
    void    setY   (const QString &y   );

private:
    QString _name;
    QString _y;


};

bool operator==(const IntermodTrace &left, const IntermodTrace &right);

#endif // INTERMODTRACE_H
