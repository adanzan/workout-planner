// This class is used to hold the individual exercises as a class instance
#ifndef EXERCISE_H
#define EXERCISE_H

#include <QStringList>

class Exercise {
public:
    // Constructor for an exercise
    Exercise(QString name, quint64 primary, quint64 secondary, QStringList equipmentList);
    // Name of exercise
    QString _name;
    // Muscle groups the exercise uses
    quint64 _primary, _secondary;
    // List of equipments required
    QStringList _equipmentList;

    // The list of the exercises
    static std::list<Exercise> exerciseList;

    // Method that fills in the exerciseList from the exercise list file.
    static void readExerciseList();
};

#endif // EXERCISE_H
