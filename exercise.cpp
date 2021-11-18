#include "exercise.h"

#include <QFile>
#include <QString>
#include <QTextStream>

Exercise::Exercise(){ }

void Exercise::readExerciseList(){
    // The file path of the list of exercises
    const QString EXERCISE_LIST_FILE_PATH = ":/data/exercise_list.tsv";

    QFile fileExerciseList(EXERCISE_LIST_FILE_PATH);
    // Warns if the file was unable to be opened.
    if (!fileExerciseList.open(QIODevice::ReadOnly))
        ;
        // TODO: Popup Message Boxes
        //cerr << "Was not able to open the equipment list file";
    QTextStream exerciseText(&fileExerciseList);
    QString temp;
    QStringList splitList;
    while(!exerciseText.atEnd()){
        exerciseText >> temp;
        splitList = temp.split("\t");
        if (splitList.isEmpty()){
            continue;
        }
        QString name = splitList.at(0);
        QStringList exercise;




    }

}
