QT += widgets
requires(qtConfig(filedialog))

HEADERS       = mainwindow.h \
                mdichild.h \
                muscle_encoding.h
SOURCES       = main.cpp \
                mainwindow.cpp \
                mdichild.cpp \
                muscle_encoding.cpp
RESOURCES     = mdi.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows/mdi
INSTALLS += target
