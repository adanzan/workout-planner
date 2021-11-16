#ifndef EXERCISE_H
#define EXERCISE_H

// Q: Is this ok, or should I do class QString instead?
#include <QString>
#include <QStringList>

class Exercise {
public:
    Exercise();
    QString name;
    QStringList equipment;
    quint64 primary, secondary;
};

#endif // EXERCISE_H
