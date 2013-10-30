QT += core widgets gui

SOURCES += \
    mainwindow.cpp \
    main.cpp \
    imghdl.cpp

HEADERS += \
    mainwindow.h \
    imghdl.h

RESOURCES += \
    icons.qrc


# Specifies the head file directories that should be searched.
INCLUDEPATH += C:/opencv/build/include/
INCLUDEPATH += C:/opencv/build/include/opencv/
INCLUDEPATH += C:/opencv/build/include/opencv2/

# Contains the list of library files that should be linked with the project.
LIBS += -LC:/opencv/build/x64/vc11/lib \
        -lopencv_core244 \
        -lopencv_highgui244 \
        -lopencv_imgproc244
