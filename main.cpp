#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include "exercise.h"
#include "mainwindow.h"

#include "iostream"

using namespace std;

int main(int argc, char *argv[]) {
    Q_INIT_RESOURCE(mdi);

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

    Exercise::readExerciseList();

    MainWindow mainWin;
    const QStringList posArgs = parser.positionalArguments();
    for (const QString &fileName : posArgs)
        mainWin.openFile(fileName);
    mainWin.show();
    return app.exec();
}
