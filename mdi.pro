QT += widgets xml printsupport
requires(qtConfig(filedialog))

HEADERS       = mainwindow.h \
                exercise.h \
                mdichild.h \
                muscleencoding.h \
                musclemap.h \
                mylistwidget.h \
                mytreewidget.h \
                qgraphicsmusclegroup.h
SOURCES       = main.cpp \
                exercise.cpp \
                mainwindow.cpp \
                mdichild.cpp \
                muscleencoding.cpp \
                musclemap.cpp \
                mylistwidget.cpp \
                mytreewidget.cpp \
                qgraphicsmusclegroup.cpp
RESOURCES     = mdi.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows/mdi
INSTALLS += target

DISTFILES += \
    data/CSCI0318 - Workout Project - Sheet1.tsv \
    data/CSCI0318 - Workout Project - Sheet1.txt \
    data/CSCI0318 - Workout Project - Sheet1.txt
