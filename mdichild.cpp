#include <QtWidgets>
#include <QPixmap>

#include "mdichild.h"
#include "muscleencoding.h"
#include "exercise.h"

#include "musclemap.h"

#include <list>

using namespace std;

// Loads the images
void MdiChild::loadImages() {
    // The size of the images
    const int size = 200;
    QImage aBench(":/images/adjustable bench.jpg");
    equipPix["Adjustable Bench"] = QPixmap::fromImage(aBench.scaled(size, size, Qt::KeepAspectRatio));
    QImage barbell(":/images/barbell.jpg");
    equipPix["Barbell"] = QPixmap::fromImage(barbell.scaled(size, size, Qt::KeepAspectRatio));
    QImage bench(":/images/bench.jpg");
    equipPix["Bench"] = QPixmap::fromImage(bench.scaled(size, size, Qt::KeepAspectRatio));
    QImage cabMachine(":/images/cable machine.jpg");
    equipPix["Cable Machine"] = QPixmap::fromImage(cabMachine.scaled(size, size, Qt::KeepAspectRatio));
    QImage cRaise(":/images/calf raise.jpg");
    equipPix["Calf Raise Machine"] = QPixmap::fromImage(cRaise.scaled(size, size, Qt::KeepAspectRatio));
    QImage cBar(":/images/curl bar.jpg");
    equipPix["Curl Bar"] = QPixmap::fromImage(cBar.scaled(size, size, Qt::KeepAspectRatio));
    QImage dBar(":/images/dip bar.jpg");
    equipPix["Dip Bar"] = QPixmap::fromImage(dBar.scaled(size, size, Qt::KeepAspectRatio));
    QImage dBells(":/images/dumbbells.jpg");
    equipPix["Dumbbells"] = QPixmap::fromImage(dBells.scaled(size, size, Qt::KeepAspectRatio));
    QImage hCurl(":/images/hamstring curl machine.jpg");
    equipPix["Hamstring Curl Machine"] = QPixmap::fromImage(hCurl.scaled(size, size, Qt::KeepAspectRatio));
    QImage hAb(":/images/hip abductor machine.jpg");
    equipPix["Hip Abductor Machine"] = QPixmap::fromImage(hAb.scaled(size, size, Qt::KeepAspectRatio));
    QImage hThrust(":/images/hip thrust machine.jpg");
    equipPix["Hip Thrust Machine"] = QPixmap::fromImage(hThrust.scaled(size, size, Qt::KeepAspectRatio));
    QImage lPull(":/images/lat-pulldown.jpg");
    equipPix["Lat Pulldown Machine"] = QPixmap::fromImage(lPull.scaled(size, size, Qt::KeepAspectRatio));
    QImage pBar(":/images/pull up bar.jpg");
    equipPix["Pull Up Bar"] = QPixmap::fromImage(pBar.scaled(size, size, Qt::KeepAspectRatio));
    QImage qExt(":/images/quad extension machine.jpg");
    equipPix["Quad Extension Machine"] = QPixmap::fromImage(qExt.scaled(size, size, Qt::KeepAspectRatio));
    QImage rack(":/images/squat rack.jpg");
    equipPix["Squat Rack"] = QPixmap::fromImage(rack.scaled(size, size, Qt::KeepAspectRatio));
}

MdiChild::MdiChild() {
    setAttribute(Qt::WA_DeleteOnClose);
    isUntitled = true;
    // Setting the HBox layout to be the main layout
    QHBoxLayout *mainLayout = new QHBoxLayout();
    setLayout(mainLayout);

    equipPixLayout = new QVBoxLayout();
    mainLayout->addLayout(equipPixLayout);

    loadImages();
    QLabel* label = new QLabel;
        //Q: Do we need this?
    label->setPixmap(equipPix["Barbell"]);
    equipPixLayout->addWidget(label);

    // A tree widget to display the exercises
    exerciseTreeWidget = new QTreeWidget();
    mainLayout->addWidget(exerciseTreeWidget);
    exerciseTreeWidget->setColumnCount(3);
    exerciseTreeWidget->setHeaderLabels(QStringList() << "Exercise" << "Primary" << "Secondary");

    // Buttons to add / remove exercises to the routine
    //TODO: In the future, consider changing this out so that it works for arrow keys; and get rid of the button
    QVBoxLayout *editRoutineButtonLayout = new QVBoxLayout();
    mainLayout->addLayout(editRoutineButtonLayout);

    // Button to add an exercise
    buttonAddExercise = new QPushButton("Add");
    editRoutineButtonLayout->addWidget(buttonAddExercise);
    connect(buttonAddExercise, &QPushButton::clicked, this, &MdiChild::buttonAddExerciseClicked);

    // Button to remove
    buttonRemoveExercise = new QPushButton("Remove");
    editRoutineButtonLayout->addWidget(buttonRemoveExercise);
    connect(buttonRemoveExercise, &QPushButton::clicked, this, &MdiChild::buttonRemoveExerciseClicked);

    // Widget to construct the routine
    routineLayout = new QVBoxLayout();
    routineListWidget = new QListWidget();
    routineLayout->addWidget(routineListWidget);
    mainLayout->addLayout(routineLayout);

    // Button print the routine
    buttonPrintRoutine = new QPushButton("Print");
    routineLayout->addWidget(buttonPrintRoutine);
    connect(buttonPrintRoutine, &QPushButton::clicked, this, &MdiChild::buttonPrintRoutineClicked);

    // Button to analyze the routine
    buttonAnalyzeRoutine = new QPushButton("Analyze");
    routineLayout->addWidget(buttonAnalyzeRoutine);
    connect(buttonAnalyzeRoutine, &QPushButton::clicked, this, &MdiChild::buttonAnalyzeRoutineClicked);

    // Vector drawing of the muscles being worked
    muscleMapWidget = new MuscleMap();
    mainLayout->addWidget(muscleMapWidget);

    // Loops for each exercise in the list of exercises
    for (Exercise &exercise : Exercise::exerciseList) {
        QTreeWidgetItem *exerciseItem = new QTreeWidgetItem(exerciseTreeWidget);

        // Exercise Name
        exerciseItem->setText(0, exercise._name);

        //Primary Muscle Group
        if (MuscleEncoding::decodeMuscleGroup(exercise._primary).isEmpty()) {
            //TODO:Warning that the file was not read correctly, primary muscles were incorrectly entered
        } else exerciseItem->setText(1, MuscleEncoding::decodeMuscleGroup(exercise._primary)[0]);

        //Secondary Muscle Group
        exerciseItem->setText(2, MuscleEncoding::decodeMuscleGroup(exercise._secondary).join(",  "));

        // Equipments Used
        for (QString &equipment : exercise._equipmentList) {
            QTreeWidgetItem *exerciseItemEquipment = new QTreeWidgetItem(exerciseItem);
            exerciseItemEquipment->setText(0, equipment);
        }

        // Stores data about the muscles being worked
        exerciseItem->setData(0, PRIMARY, exercise._primary);
        exerciseItem->setData(0, SECONDARY, exercise._secondary);

    }
    connect(exerciseTreeWidget, &QTreeWidget::currentItemChanged, this, &MdiChild::exerciseSelectedItemChanged);
    // Connects the muscle map widget to the muscle selection changed method in the muscle map class
    connect(muscleMapWidget, &MuscleMap::selectionChanged, this, &MdiChild::muscleSelectionChanged);
}

// Reacts to the changes of selection on the tree widget
void MdiChild::exerciseSelectedItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous) {
    // Changes the color for all bits back to gray
    muscleMapWidget->setMuscleGroupBaseColors(~0, Qt::gray);

    QTreeWidgetItem *parentItem = current->parent();
    // If parentItem is not null, sets the colorItem to the parentItem
    QTreeWidgetItem *colorItem = parentItem ? parentItem:current;
    muscleMapWidget->setMuscleGroupBaseColors(colorItem->data(0, PRIMARY).toInt(), Qt::red);
    muscleMapWidget->setMuscleGroupBaseColors(colorItem->data(0, SECONDARY).toInt(), Qt::yellow);

    if (parentItem) {}
}

void MdiChild::muscleSelectionChanged(int bits) {
    // Loops through the tree widget
    for (int i = exerciseTreeWidget->topLevelItemCount(); --i>=0;) {
        QTreeWidgetItem *item = exerciseTreeWidget->topLevelItem(i);
        int exerciseBits = item->data(0, PRIMARY).toInt() | item->data(0, SECONDARY).toInt();
        // Set the exercises that don't work the muscle to hidden
        // Also, show everything if nothing is selected
        item->setHidden(bits && !(bits & exerciseBits));
    }
}

// Prints the routine
void MdiChild::buttonPrintRoutineClicked() {}

// Analyzes the routine (heatmap)
void MdiChild::buttonAnalyzeRoutineClicked() {
    int colorBitMaxValue = 2 * (routineListWidget->count()) + 1;
    // A vector that stores which muscles should be colored?
    vector<int> colorBits(colorBitMaxValue, 0);
    // Sets all the muscles worked to 0?
    colorBits[0] = ~0;

    // Loops through the routineListWidget
    for (int i = 0; i < routineListWidget->count(); i++) {
        QListWidgetItem *routineItem = routineListWidget->item(i);
        // Loops through the colorBit and adds the primary bits
        for (int j=colorBitMaxValue; --j>=0;) {
            int moveBits = colorBits[j] & routineItem->data(PRIMARY).toInt();
            // If there are exercises to move, move them
            if (moveBits) {
                colorBits[j] &= ~moveBits;
                colorBits[j+2] |= moveBits;
            }
        }
        //Loops through the colorbit and adds the secondary bits
        for (int j=colorBitMaxValue; --j>=0;) {
            int moveBits = colorBits[j] & routineItem->data(SECONDARY).toInt();
            if (moveBits) {
                colorBits[j] &= ~moveBits;
                colorBits[j+1] |= moveBits;
            }
        }
    }
    //Coloring stuff here
    for (int i=0; i<colorBitMaxValue; i++) {
        QColor color;
        if (i == 0)
            color = Qt::gray;
        else {
            double hue = i * 2.0 / 27.0;
            if (hue > 2.0 / 3.0) hue = 5.0 / 6.0;
            color = QColor::fromHsvF(hue, 1.0, 1.0);
        }
        muscleMapWidget->setMuscleGroupBaseColors(colorBits[i], color);
    }
}

// Adds an exercise to the routine
void MdiChild::buttonAddExerciseClicked() {
    // Creates a temporary list item and adds it to the routine
    QListWidgetItem *tempListItem = new QListWidgetItem;
    QTreeWidgetItem *currentItem = exerciseTreeWidget->currentItem();
    // If the current item has a parent, set current item to its parent
    if (currentItem->parent()) currentItem = currentItem->parent();

    tempListItem->setText(currentItem->text(0));
    tempListItem->setData(PRIMARY, currentItem->data(0, PRIMARY));
    tempListItem->setData(SECONDARY, currentItem->data(0, SECONDARY));
    routineListWidget->insertItem(routineListWidget->count(), tempListItem);
}

// Removes an exercise from the routine
void MdiChild::buttonRemoveExerciseClicked() {
    // Removes the list widget at the current row
    routineListWidget->takeItem(routineListWidget->currentRow());
}

void MdiChild::newFile() {
    static int sequenceNumber = 1;

    isUntitled = true;
    curFile = tr("document%1.txt").arg(sequenceNumber++);
    setWindowTitle(curFile + "[*]");

}

bool MdiChild::loadFile(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("MDI"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream in(&file);
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    // Read file here
    QGuiApplication::restoreOverrideCursor();

    setCurrentFile(fileName);

    return true;
}

bool MdiChild::save() {
    if (isUntitled) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}

bool MdiChild::saveAs() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                                    curFile);
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
}

bool MdiChild::saveFile(const QString &fileName) {
    QString errorMessage;

    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    QSaveFile file(fileName);
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream out(&file);
        // Output file
        if (!file.commit()) {
            errorMessage = tr("Cannot write file %1:\n%2.")
                    .arg(QDir::toNativeSeparators(fileName), file.errorString());
        }
    } else {
        errorMessage = tr("Cannot open file %1 for writing:\n%2.")
                .arg(QDir::toNativeSeparators(fileName), file.errorString());
    }
    QGuiApplication::restoreOverrideCursor();

    if (!errorMessage.isEmpty()) {
        QMessageBox::warning(this, tr("MDI"), errorMessage);
        return false;
    }

    setCurrentFile(fileName);
    return true;
}

QString MdiChild::userFriendlyCurrentFile() {
    return strippedName(curFile);
}

void MdiChild::closeEvent(QCloseEvent *event) {
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}

void MdiChild::documentWasModified() { }

bool MdiChild::maybeSave() {
    // If something has been modified
    if (false)
        return true;
    const QMessageBox::StandardButton ret
            = QMessageBox::warning(this, tr("MDI"),
                                   tr("'%1' has been modified.\n"
                                      "Do you want to save your changes?")
                                   .arg(userFriendlyCurrentFile()),
                                   QMessageBox::Save | QMessageBox::Discard
                                   | QMessageBox::Cancel);
    switch (ret) {
    case QMessageBox::Save:
        return save();
    case QMessageBox::Cancel:
        return false;
    default:
        break;
    }
    return true;
}

void MdiChild::setCurrentFile(const QString &fileName) {
    curFile = QFileInfo(fileName).canonicalFilePath();
    isUntitled = false;

    //  document()->setModified(false);
    setWindowModified(false);
    setWindowTitle(userFriendlyCurrentFile() + "[*]");
}

QString MdiChild::strippedName(const QString &fullFileName) {
    return QFileInfo(fullFileName).fileName();
}
