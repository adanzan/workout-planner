/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>
#include <QPixmap>

#include "mdichild.h"
#include "muscleencoding.h"
#include "exercise.h"

#include "musclemap.h"

#include <list>

using namespace std;

// Constant values that will be used in setting the data on the muscles being worked
//TODO: Add into enum in header
const int PRIMARY = Qt::UserRole;
const int SECONDARY = Qt::UserRole + 1;

MdiChild::MdiChild() {
    setAttribute(Qt::WA_DeleteOnClose);
    isUntitled = true;
    // Setting the HBox layout
    QHBoxLayout *main_layout = new QHBoxLayout();
    setLayout(main_layout);

    equipPixLayout = new QVBoxLayout();
    main_layout->addLayout(equipPixLayout);
    QLabel* label = new QLabel;
    label->setPixmap(equipPix["Barbell"]);
    equipPixLayout->addWidget(label);

    exerciseTreeWidget = new QTreeWidget();
    main_layout->addWidget(exerciseTreeWidget);


    //Add QListWidget to build the exericse routine
    // It will need to connect to the muscles worked, since clicking on the exerciese nees to change the muscles worked
    // Add 2 buttons (left and right) so that
        // See if I can drag the listwidget items
        // Think about how I want the user to work with the list widget
            // Could maybe have how many times a muscle is being worked
            // Will probably have a
            // Could also print the exercises at the end

    // QList and Heatmap

    muscleMapWidget = new MuscleMap();
    main_layout->addWidget(muscleMapWidget);

    QImage barbell(":/images/barbell.jpg");
    equipPix["Barbell"] = QPixmap::fromImage(barbell);
    QImage bench(":/images/bench.jpg");
    equipPix["Bench"] = QPixmap::fromImage(bench);
    QImage cabMachine(":/images/cable machine.jpg");
    equipPix["Cable Machine"] = QPixmap::fromImage(cabMachine);
    QImage aBench(":/images/adjustable bench.jpg");
    equipPix["Adjustable Bench"] = QPixmap::fromImage(aBench);
    QImage cBar(":/images/curl bar.jpg");
    equipPix["Curl Bar"] = QPixmap::fromImage(cBar);
    QImage dBar(":/images/dip bar.jpg");
    equipPix["Dip Bar"] = QPixmap::fromImage(dBar);
    QImage hCurl(":/images/hamstring curl machine.jpg");
    equipPix["Hamstring Curl Machine"] = QPixmap::fromImage(hCurl);
    QImage hAb(":/images/hip abductor machine.jpg");
    equipPix["Hip Abductor Machine"] = QPixmap::fromImage(hAb);
    QImage hThrust(":/images/hip thrust machine.jpg");
    equipPix["Hip Thrust Machine"] = QPixmap::fromImage(hThrust);
    QImage pBar(":/images/pull up bar.jpg");
    equipPix["Pull Up Bar"] = QPixmap::fromImage(pBar);
    QImage qExt(":/images/quad extension machine.jpg");
    equipPix["Quad Extension Machine"] = QPixmap::fromImage(qExt);

        // Sets up the tree widget
    exerciseTreeWidget->setColumnCount(3);
    exerciseTreeWidget->setHeaderLabels(QStringList() << "Exercise" << "Primary" << "Secondary");

    // Loops for each exercise in the list of exercises
    for (Exercise &exercise : Exercise::exerciseList) {
        QTreeWidgetItem *exerciseItem = new QTreeWidgetItem(exerciseTreeWidget);

        // Exercise name
        exerciseItem->setText(0, exercise._name);

        //Primary Muscle Group
        if (MuscleEncoding::decodeMuscleGroup(exercise._primary).isEmpty()){
            //Warning that the file was not read correctly, primary muscles were incorrectly entered
        }
        else exerciseItem->setText(1, MuscleEncoding::decodeMuscleGroup(exercise._primary)[0]);

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
    connect(exerciseTreeWidget, &QTreeWidget::itemClicked, this, &MdiChild::exerciseClicked);
    // Connects the muscle map widget to the muscle selection changed method in the muscle map class
    connect(muscleMapWidget, &MuscleMap::selectionChanged, this, &MdiChild::muscleSelectionChanged);

}
// TODO: Change this to selected / check the signals
void MdiChild::exerciseClicked(QTreeWidgetItem *item, int column) {
    // Changes the color for all bits back to gray
    muscleMapWidget->setMuscleGroupBaseColors(~0, Qt::gray);

    muscleMapWidget->setMuscleGroupBaseColors(item->data(0, PRIMARY).toInt(), Qt::red);
    muscleMapWidget->setMuscleGroupBaseColors(item->data(0, SECONDARY).toInt(), Qt::yellow);
}

void MdiChild::muscleSelectionChanged(int bits) {
//    qDebug() << bits;
    // Loops through the tree widget
    for (int i = exerciseTreeWidget->topLevelItemCount(); --i>=0;){
        QTreeWidgetItem *item = exerciseTreeWidget->topLevelItem(i);
        int exerciseBits = item->data(0, PRIMARY).toInt() | item->data(0, SECONDARY).toInt();

        // Set the exercises that don't work the muscle to hidden
        // Also, show everything if nothing is selected
        item->setHidden(bits && !(bits & exerciseBits));
    }
}


void MdiChild::newFile()
{
    static int sequenceNumber = 1;

    isUntitled = true;
    curFile = tr("document%1.txt").arg(sequenceNumber++);
    setWindowTitle(curFile + "[*]");

}

bool MdiChild::loadFile(const QString &fileName)
{
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

bool MdiChild::save()
{
    if (isUntitled) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}

bool MdiChild::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                                    curFile);
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
}

bool MdiChild::saveFile(const QString &fileName)
{
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

QString MdiChild::userFriendlyCurrentFile()
{
    return strippedName(curFile);
}

void MdiChild::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}

void MdiChild::documentWasModified()
{
}

bool MdiChild::maybeSave()
{
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

void MdiChild::setCurrentFile(const QString &fileName)
{
    curFile = QFileInfo(fileName).canonicalFilePath();
    isUntitled = false;

    //  document()->setModified(false);
    setWindowModified(false);
    setWindowTitle(userFriendlyCurrentFile() + "[*]");
}

QString MdiChild::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}
