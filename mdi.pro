QT += widgets
requires(qtConfig(filedialog))

HEADERS       = mainwindow.h \
                exercise.h \
                mdichild.h \
                muscleencoding.h
SOURCES       = main.cpp \
                exercise.cpp \
                mainwindow.cpp \
                mdichild.cpp \
                muscleencoding.cpp
RESOURCES     = mdi.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows/mdi
INSTALLS += target

DISTFILES += \
    data/CSCI0318 - Workout Project - Sheet1.tsv \
    data/CSCI0318 - Workout Project - Sheet1.txt \
    data/CSCI0318 - Workout Project - Sheet1.txt
