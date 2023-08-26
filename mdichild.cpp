#include <QTextLength>
#include <QTextBrowser>
#include <QTextTableFormat>
#include <QtWidgets>
#include <QPixmap>
#include <QPrinter>
#include <QPrintDialog>
#include <QKeyEvent>
#include <QVector>


#include "mdichild.h"
#include "muscleencoding.h"
#include "exercise.h"
#include "musclemap.h"

#include <list>

using namespace std;

// Loads the images
void MdiChild::loadImages() {
    // The size of the images
    const int SIZE = 200;
    QImage aBench(":/images/adjustable bench.jpg");
    equipPix["Adjustable Bench"] = QPixmap::fromImage(aBench.scaled(SIZE, SIZE, Qt::KeepAspectRatio));
    QImage barbell(":/images/barbell.jpg");
    equipPix["Barbell"] = QPixmap::fromImage(barbell.scaled(SIZE, SIZE, Qt::KeepAspectRatio));
    QImage bench(":/images/bench.jpg");
    equipPix["Bench"] = QPixmap::fromImage(bench.scaled(SIZE, SIZE, Qt::KeepAspectRatio));
    QImage cabMachine(":/images/cable machine.jpg");
    equipPix["Cable Machine"] = QPixmap::fromImage(cabMachine.scaled(SIZE, SIZE, Qt::KeepAspectRatio));
    QImage cRaise(":/images/calf raise.jpg");
    equipPix["Calf Raise Machine"] = QPixmap::fromImage(cRaise.scaled(SIZE, SIZE, Qt::KeepAspectRatio));
    QImage cBar(":/images/curl bar.jpg");
    equipPix["Curl Bar"] = QPixmap::fromImage(cBar.scaled(SIZE, SIZE, Qt::KeepAspectRatio));
    QImage dBar(":/images/dip bar.jpg");
    equipPix["Dip Bar"] = QPixmap::fromImage(dBar.scaled(SIZE, SIZE, Qt::KeepAspectRatio));
    QImage dBells(":/images/dumbbells.jpg");
    equipPix["Dumbbells"] = QPixmap::fromImage(dBells.scaled(SIZE, SIZE, Qt::KeepAspectRatio));
    QImage hCurl(":/images/hamstring curl machine.jpg");
    equipPix["Hamstring Curl Machine"] = QPixmap::fromImage(hCurl.scaled(SIZE, SIZE, Qt::KeepAspectRatio));
    QImage hAb(":/images/hip abductor machine.jpg");
    equipPix["Hip Abductor Machine"] = QPixmap::fromImage(hAb.scaled(SIZE, SIZE, Qt::KeepAspectRatio));
    QImage hThrust(":/images/hip thrust machine.jpg");
    equipPix["Hip Thrust Machine"] = QPixmap::fromImage(hThrust.scaled(SIZE, SIZE, Qt::KeepAspectRatio));
    QImage lPull(":/images/lat-pulldown.jpg");
    equipPix["Lat Pulldown Machine"] = QPixmap::fromImage(lPull.scaled(SIZE, SIZE, Qt::KeepAspectRatio));
    QImage kBell(":/images/kettlebell.jpg");
    equipPix["Kettlebells"] = QPixmap::fromImage(kBell.scaled(SIZE, SIZE, Qt::KeepAspectRatio));
    QImage pBar(":/images/pull up bar.jpg");
    equipPix["Pull Up Bar"] = QPixmap::fromImage(pBar.scaled(SIZE, SIZE, Qt::KeepAspectRatio));
    QImage qExt(":/images/quad extension machine.jpg");
    equipPix["Quad Extension Machine"] = QPixmap::fromImage(qExt.scaled(SIZE, SIZE, Qt::KeepAspectRatio));
    QImage rack(":/images/squat rack.jpg");
    equipPix["Squat Rack"] = QPixmap::fromImage(rack.scaled(SIZE, SIZE, Qt::KeepAspectRatio));
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

    // A tree widget to display the exercises
    exerciseTreeWidget = new MyTreeWidget();
    mainLayout->addWidget(exerciseTreeWidget);
    exerciseTreeWidget->setColumnCount(3);
    exerciseTreeWidget->setHeaderLabels(QStringList() << "Exercise" << "Primary" << "Secondary");
    connect(exerciseTreeWidget, &MyTreeWidget::enterKeyPressed, this, &MdiChild::buttonAddExerciseClicked);

    // Buttons to add / remove exercises to the routine
    QVBoxLayout *editRoutineButtonLayout = new QVBoxLayout();
    mainLayout->addLayout(editRoutineButtonLayout);

    // Button to add an exercise
    buttonAddExercise = new QPushButton("Add Exercise");
    editRoutineButtonLayout->addWidget(buttonAddExercise);
    connect(buttonAddExercise, &QPushButton::clicked, this, &MdiChild::buttonAddExerciseClicked);

    // Button to remove an exercise
    buttonRemoveExercise = new QPushButton("Remove Exercise");
    editRoutineButtonLayout->addWidget(buttonRemoveExercise);
    connect(buttonRemoveExercise, &QPushButton::clicked, this, &MdiChild::buttonRemoveExerciseClicked);

    // Widget to construct the routine
    routineLayout = new QVBoxLayout();
    routineListWidget = new MyListWidget();
    connect(routineListWidget, &MyListWidget::backspaceKeyPressed, this, &MdiChild::buttonRemoveExerciseClicked);
    routineLayout->addWidget(routineListWidget);
    mainLayout->addLayout(routineLayout);

    // Button to print the routine
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

        // Primary Muscle Group
        if (MuscleEncoding::decodeMuscleGroup(exercise._primary).isEmpty()) {
            QMessageBox::warning(this, tr("Workout Planner"), "File read incorrectly, primary muscle group is empty for an exercise");
        } else exerciseItem->setText(1, MuscleEncoding::decodeMuscleGroup(exercise._primary)[0]);

        // Secondary Muscle Group
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
void MdiChild::exerciseSelectedItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *) {
    // Changes the color for all bits back to gray
    muscleMapWidget->setMuscleGroupBaseColors(~0, Qt::gray);

    QTreeWidgetItem *parentItem = current->parent();
    // If parentItem is not null, sets the colorItem to the parentItem
    QTreeWidgetItem *colorItem = parentItem ? parentItem:current;
    muscleMapWidget->setMuscleGroupBaseColors(colorItem->data(0, PRIMARY).toInt(), Qt::red);
    muscleMapWidget->setMuscleGroupBaseColors(colorItem->data(0, SECONDARY).toInt(), Qt::yellow);

    // Changes the selected item on the routine widget
    routineListSelectionChanged();

    // If the item is an equipment
    if (parentItem) {
        QString thisEquipment = current->text(0);
        QLayoutItem *child;
        while ((child = equipPixLayout->takeAt(0))) {
            delete child->widget();
            delete child;
        }

        // Displays the picture of the equipment
        for (auto equipment = equipPix.begin(); equipment != equipPix.end(); ++equipment) {
            if (thisEquipment.contains(equipment.key())) {
                qDebug()<<equipment.key();
                QLabel* label = new QLabel;
                label->setPixmap(equipPix[equipment.key()]);
                equipPixLayout->addWidget(label);
            }
        }
    }
}

// Changes the muscle selection based on the muscle map
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
void MdiChild::buttonPrintRoutineClicked() {
    int n = routineListWidget->count();
    //Creates the preset formatting for the table
    QTextTableFormat format;
    format.setCellPadding(50);
    format.setHeight(3000/(n+1));
    format.setWidth(2000);
    QTextEdit *edit = new QTextEdit();
    QTextCursor cursor(edit->textCursor());
    cursor.movePosition(QTextCursor::Start);

    //Creates the table to print
    QTextTable *table = cursor.insertTable(n+1, 3, format);
    table->cellAt(0, 0).firstCursorPosition().insertText("Exercise");
    for (int i = 0; i < n; i++) {
        QString exercise = routineListWidget->item(i)->text();
        table->cellAt(i+1, 0).firstCursorPosition().insertText(exercise);
    }
    table->cellAt(0, 1).firstCursorPosition().insertText("Sets");
    table->cellAt(0, 2).firstCursorPosition().insertText("Reps");
    edit->show();

    //Prints the table
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog printDialog(&printer);
    if (printDialog.exec() == QDialog::Accepted){
        QPainter painter(&printer);
        edit->document()->documentLayout()->setPaintDevice(painter.device());
        edit->document()->drawContents(&painter);
    }
    delete edit;
}

// Analyzes the routine and colors the heatmap of the muscles worked.
void MdiChild::buttonAnalyzeRoutineClicked() {
    int colorBitMaxValue = 2 * (routineListWidget->count()) + 1;
    // A vector that stores which muscles should be colored?
    vector<int> colorBits(colorBitMaxValue, 0);
    // Sets the rest of the muscles 0
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

    // Adds the QListWidgetItem
    tempListItem->setText(currentItem->text(0));
    tempListItem->setData(PRIMARY, currentItem->data(0, PRIMARY));
    tempListItem->setData(SECONDARY, currentItem->data(0, SECONDARY));
    routineListWidget->insertItem(routineListWidget->count(), tempListItem);
}

// Changes the selection of the list based on the tree widget and other factors
void MdiChild::routineListSelectionChanged() {
    QTreeWidgetItem *currentItem = exerciseTreeWidget->currentItem();
    // If the current item has a parent, set current item to its parent
    if (currentItem->parent()) currentItem = currentItem->parent();

    // Loops through the listWidget and selects the last element that is selected in the treeWidget
    for (int i = 0; i < routineListWidget->count(); i++) {
        QListWidgetItem *routineItem = routineListWidget->item(i);
        if (currentItem->text(0) == routineItem->text()) routineItem->setSelected(1);
    }
}

// Removes an exercise from the routine
void MdiChild::buttonRemoveExerciseClicked() {
    // Removes the currently selected listWidget items.
    QList<QListWidgetItem*> items = routineListWidget->selectedItems();
    foreach(QListWidgetItem * item, items) {
        routineListWidget->takeItem(routineListWidget->row(item));
    }
    routineListSelectionChanged();
}

void MdiChild::newFile() {
    static int sequenceNumber = 1;
    isUntitled = true;
    curFile = tr("workout_plan%1.txt").arg(sequenceNumber++);
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
    if (isUntitled) return saveAs();
        else return saveFile(curFile);
}

bool MdiChild::saveAs() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                                    curFile);
    if (fileName.isEmpty()) return false;

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
    if (maybeSave()) event->accept();
    else event->ignore();
}

void MdiChild::documentWasModified() { }

bool MdiChild::maybeSave() {
    // If something has been modified
    if (false) return true;
    const QMessageBox::StandardButton ret
            = QMessageBox::warning(this, tr("MDI"),
                                   tr("'%1' has been modified.\n"
                                      "Do you want to save your changes?")
                                   .arg(userFriendlyCurrentFile()),
                                   QMessageBox::Save | QMessageBox::Discard
                                   | QMessageBox::Cancel);
    switch (ret) {
    case QMessageBox::Save: return save();
    case QMessageBox::Cancel: return false;
    default: break;
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
