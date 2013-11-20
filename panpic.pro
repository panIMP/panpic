QT += core widgets gui

SOURCES += \
    main.cpp \
    uimainwindow.cpp \
    panimage.cpp \
    panimageio.cpp \
    panimageshift.cpp \
    panimagehistproc.cpp \
    uihistdialog.cpp \
    panimagefilter.cpp

HEADERS += \
    uimainwindow.h \
    panimage.h \
    panimageio.h \
    panimageshift.h \
    panimagehistproc.h \
    uihistdialog.h \
    panimagefilter.h

RESOURCES += \
    icons.qrc


# Specifies the head file directories that should be searched.
INCLUDEPATH += C:/opencv/build/include/
INCLUDEPATH += C:/opencv/build/include/opencv/
INCLUDEPATH += C:/opencv/build/include/opencv2/

# Contains the list of library files that should be linked with the project.
LIBS += -LC:/opencv/build/x64/vc11/lib \
        -lopencv_core244d \
        -lopencv_highgui244d \
        -lopencv_imgproc244d \
        -lopencv_video244d
