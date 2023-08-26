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

// Reads the exercise file and populates the exercise list.
void Exercise::readExerciseList() {
    // Opens file
    const QString EXERCISE_LIST_FILE_PATH = ":/data/exercise_list.tsv";
    QFile fileExerciseList(EXERCISE_LIST_FILE_PATH);

    // Warns if the file was unable to be opened.
    if (!fileExerciseList.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(nullptr, "Error", "Unable to open the exercise list file");
        return;
    }

    // Populates the exercise list from the file
    QTextStream exerciseText(&fileExerciseList);
    QString line;
    QStringList splitLine;

    // Loop through the stream
    while (!exerciseText.atEnd()) {
        line = exerciseText.readLine();
        splitLine = line.split("\t");
        if (splitLine.isEmpty()) continue;

        // Assigns the tab seperated values
        QString name = splitLine.at(0);
        quint64 primary = MuscleEncoding::encodeMuscleGroup(QStringList(splitLine.at(1)));
        quint64 secondary = MuscleEncoding::encodeMuscleGroup(QStringList(splitLine.at(2).split(", ")));
        QStringList equipmentList = splitLine.at(3).split(", ");
        // Pushes the exercise onto the list of exercises
        exerciseList.push_back(Exercise(name, primary, secondary, equipmentList));
    }
}
