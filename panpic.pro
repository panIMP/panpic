QT += core widgets gui

SOURCES += \
    main.cpp \
    algDetect.cpp \
    algFeatExtract.cpp \
    algFilter.cpp \
    algHistProc.cpp \
    algShift.cpp \
    uiHistDlg.cpp \
    uiHoughDlg.cpp \
    uiMainWin.cpp \
    baseImage.cpp \
    baseThread.cpp

HEADERS += \
    algDetect.h \
    algFeatExtract.h \
    algFilter.h \
    algHistProc.h \
    algShift.h \
    uiHistDlg.h \
    uiHoughDlg.h \
    uiMainWin.h \
    baseImage.h \
    baseTransform.h \
    baseThread.h

RESOURCES += \
    icons.qrc


# Specifies the head file directories that should be searched.
INCLUDEPATH += G:/opencv/build/include/
INCLUDEPATH += G:/opencv/build/include/opencv/
INCLUDEPATH += G:/opencv/build/include/opencv2/

# Contains the list of library files that should be linked with the project.
LIBS += -LG:/opencv/build/x64/vc11/lib \
        -lopencv_core247d \
        -lopencv_highgui247d \
        -lopencv_imgproc247d \
        -lopencv_video247d
