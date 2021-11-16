//CS318
//Workout Project
//Created by Danzan and Will

#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QFile>
#include <QTreeWidget>

#include "mainwindow.h"

#include "iostream"

using namespace std;

// The file path of the list of exercises
const QString EXERCISE_LIST_FILE_PATH = ":/data/exercise_list.tsv";

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(mdi);

    QFile fileExerciseList(EXERCISE_LIST_FILE_PATH);
    // Warns if the file was unable to be opened.
    if (!fileExerciseList.open(QIODevice::ReadOnly))
        cerr << "Was not able to open the equipment list file";

    QTreeWidget *ExerciseList = new QTreeWidget();
    // Q: QTreeItem? List? QList of QTreeItems?



    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("MDI Example");
    QCoreApplication::setOrganizationName("QtProject");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    QCommandLineParser parser;
    parser.setApplicationDescription("Qt MDI Example");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("file", "The file to open.");
    parser.process(app);

    MainWindow mainWin;
    const QStringList posArgs = parser.positionalArguments();
    for (const QString &fileName : posArgs)
        mainWin.openFile(fileName);
    mainWin.show();
    return app.exec();
}
