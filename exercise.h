// This class is used to hold the individual exercises as a class instance
#ifndef EXERCISE_H
#define EXERCISE_H

#include <QStringList>

class Exercise {
public:
    // Constructor for an exercise
    Exercise(QString name, quint64 primary, quint64 secondary, QStringList equipmentList);
    QString _name;
    quint64 _primary, _secondary;
    QStringList _equipmentList;

    // The list of the exercises
    static std::list<Exercise> exerciseList;

    // This method takes in the exercise list file and fills in the exerciseList.
    static void readExerciseList();
};

#endif // EXERCISE_H
