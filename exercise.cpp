#include "exercise.h"
#include "muscleencoding.h"

#include <QFile>
#include <QString>
#include <list>
#include <QTextStream>
#include <QMessageBox>

using namespace std;

// Implementing the list of exercises
list<Exercise> Exercise::exerciseList;

// Constructor method for the exercise class
Exercise::Exercise(QString name, quint64 primary, quint64 secondary, QStringList equipmentList) {
    _name = name;
    _primary = primary;
    _secondary = secondary;
    _equipmentList = equipmentList;
}

// Reads the file of the exercises and populates the exercise list.
void Exercise::readExerciseList() {
    // The file path of the list of exercises
    const QString EXERCISE_LIST_FILE_PATH = ":/data/exercise_list.tsv";

    // Opens the file specified by the file path
    QFile fileExerciseList(EXERCISE_LIST_FILE_PATH);

    // Warns if the file was unable to be opened.
    if (!fileExerciseList.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(nullptr, "Error", "Was not able to open the exercise list file");
        return;
    }

    // Populates the exercise list from the file
    QTextStream exerciseText(&fileExerciseList);
    // Temporary variable created for each line
    QString line;
    // A QStringList of the line, created by splitting "line" by tabs
    QStringList splitLine;
    // While the exercise list file is not at the end
    while (!exerciseText.atEnd()) {
        line = exerciseText.readLine();
        // Splits the elements by tab
        splitLine = line.split("\t");
        if (splitLine.isEmpty()) continue;
        // The name of the exercise
        QString name = splitLine.at(0);
        // The coding of the primary muscle worked
        quint64 primary = MuscleEncoding::encodeMuscleGroup(QStringList(splitLine.at(1)));
        // The coding of the secondary muscle groups worked, created by splitting by comma
        quint64 secondary = MuscleEncoding::encodeMuscleGroup(QStringList(splitLine.at(2).split(", ")));
        // The list of equipments required to perform the exercise
        QStringList equipmentList = splitLine.at(3).split(", ");
        // Pushes the exercise onto the list of exercises
        exerciseList.push_back(Exercise(name, primary, secondary, equipmentList));
    }
}
