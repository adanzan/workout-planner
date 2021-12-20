// This is the main file used to build the routine
#ifndef MDICHILD_H
#define MDICHILD_H

#include "mytreewidget.h"
#include "mylistwidget.h"
#include <QGraphicsItem>
#include <QPushButton>
#include "musclemap.h"
class QVBoxLayout;

class MdiChild : public QWidget {
    Q_OBJECT

public:
    MdiChild();

    void newFile();
    bool loadFile(const QString &fileName);
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);
    QString userFriendlyCurrentFile();
    QString currentFile() { return curFile; }

    QPushButton *buttonPrintRoutine;
    QPushButton *buttonAnalyzeRoutine;

    QPushButton *buttonAddExercise;
    QPushButton *buttonRemoveExercise;
protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void documentWasModified();
    void exerciseSelectedItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void muscleSelectionChanged(int bits);

    void buttonPrintRoutineClicked();
    void buttonAnalyzeRoutineClicked();

    void buttonAddExerciseClicked();
    void buttonRemoveExerciseClicked();

private:
    bool maybeSave();
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);
    void loadImages();
    QString curFile;
    bool isUntitled;

    void arrowKeysPressed(QKeyEvent *event);
    void routineListSelectionChanged();

    QMap<QString, QPixmap> equipPix;
    QVBoxLayout *equipPixLayout;
    MyTreeWidget *exerciseTreeWidget;
    QVBoxLayout *routineLayout;
    MyListWidget *routineListWidget;
    MuscleMap *muscleMapWidget;

    // Constant values that will be used in setting the data on the muscles being worked
    enum Numbering{
        PRIMARY = Qt::UserRole,
        SECONDARY = Qt::UserRole + 1
    };
};

#endif
