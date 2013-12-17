QT += core widgets gui

SOURCES += \
    main.cpp \
    algDetect.cpp \
    algFilter.cpp \
    algHistProc.cpp \
    algShift.cpp \
    uiHistDlg.cpp \
    uiHoughDlg.cpp \
    uiMainWin.cpp \
    baseImage.cpp \
    baseThread.cpp \
    algFeatSearch.cpp

HEADERS += \
    algDetect.h \
    algFilter.h \
    algHistProc.h \
    algShift.h \
    uiHistDlg.h \
    uiHoughDlg.h \
    uiMainWin.h \
    baseImage.h \
    baseTransform.h \
    baseThread.h \
    algFeatSearch.h

RESOURCES += \
    icons.qrc


# Specifies the head file directories that should be searched.
INCLUDEPATH += G:/opencv_mingw_hpbuild/install/include/
INCLUDEPATH += G:/opencv_mingw_hpbuild/install/include/opencv/
INCLUDEPATH += G:/opencv_mingw_hpbuild/install/include/opencv2/

# Contains the list of library files that should be linked with the project.
LIBS += G:/opencv_mingw_hpbuild/install/lib/libopencv_core244d.dll.a
LIBS += G:/opencv_mingw_hpbuild/install/lib/libopencv_highgui244d.dll.a
LIBS += G:/opencv_mingw_hpbuild/install/lib/libopencv_imgproc244d.dll.a
