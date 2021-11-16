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

#include "mdichild.h"
#include "muscleencoding.h"

// 1 = Primary
// 2 = Secondary

MdiChild::MdiChild() {
    setAttribute(Qt::WA_DeleteOnClose);
    isUntitled = true;
    // Setting the HBox layout
    QHBoxLayout *main_layout = new QHBoxLayout();
    setLayout(main_layout);
    // Add layout stuff here


     exerciseList = new QTreeWidget();

     main_layout->addWidget(exerciseList);

     // Setting the column count to 3
     exerciseList->setColumnCount(3);
     // Sets the headers
     exerciseList->setHeaderLabels(QStringList() << "Exercise" << "Primary" << "Secondary");

     // Code the list into the QStringList first then do these

     // Nested for loops because there is also one for exerciseQquipment

     QTreeWidgetItem *exercise = new QTreeWidgetItem(exerciseList);
     // Exercise name
     exercise->setText(0, tr("Bench Press"));
     //Primary Muscle Group
     exercise->setText(1, tr("Chest"));
     //Secondary Muscle Group
     exercise->setText(2, tr("Biceps, Triceps"));

     // Takes an index number and puts it into the data
        // Can have them store a value behind the scenes to index it later

     // Where to put it in and what to put in
     // Puts a data in column 0
     exercise->setData(0, Qt::UserRole, MuscleEncoding::Chest);
     exercise->setData(0, Qt::UserRole + 1, MuscleEncoding::Biceps | MuscleEncoding::Triceps);



     connect(exerciseList, &QTreeWidget::itemClicked, this, &MdiChild::exerciseClicked);

     // Doing a for loop here and putting in the exercises each iteration
     QTreeWidgetItem *exerciseEquipment = new QTreeWidgetItem(exercise);
     exerciseEquipment->setText(0, tr("Barbell & Flat Bench"));

    //TODO: In the main one, we don't need to do this, we only need one.
     exerciseEquipment = new QTreeWidgetItem(exercise);
     exerciseEquipment->setText(0, tr("Dumbbells & Adjustable Bench"));

}

// How we can react to the muscle being clicked
    // Change this to selected
void MdiChild::exerciseClicked(QTreeWidgetItem *item, int column) {
    qDebug() << item->data(0, Qt::UserRole);
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
