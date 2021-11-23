#ifndef EXERCISE_H
#define EXERCISE_H

#include <QStringList>

class Exercise {
private:

public:
    Exercise(QString name, quint64 primary, quint64 secondary, QStringList equipmentList);
    QString _name;
    quint64 _primary, _secondary;
    QStringList _equipmentList;

    // TODO: Make this private
    static std::list<Exercise> exerciseList;

    // This method takes in the exercise list file and fills in the exerciseList.
    static void readExerciseList();
};

// Static list of exercises and every other file could populate from there.

#endif // EXERCISE_H
