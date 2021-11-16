#ifndef EXERCISE_H
#define EXERCISE_H

#include <QStringList>
#include <list>
    // Might not need this

class Exercise {
private:

public:
    Exercise();
    QString name;
    QStringList equipment;
    quint64 primary, secondary;

    // TODO: Make this private later
    static std::list<Exercise> exerciseList;

    // This method takes in the exercise list file and fills in the exerciseList.
    static void readExerciseList();
};

// Static list of exercises and every other file could populate from there.

#endif // EXERCISE_H
