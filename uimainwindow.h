#ifndef UIMAINWINDOW_H
#define UIMAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QImage>
#include <QLabel>
#include <QScrollArea>
#include <QToolBar>
#include <QFileInfoList>
#include <QObject>
#include <QWheelEvent>
#include <QTabWidget>
#include <QSlider>
#include <QLineEdit>
#include <QRegExpValidator>
#include <QStatusBar>
#include <QPushButton>
#include <QFileDialog>
#include <QString>
#include <QHBoxLayout>
#include <QMatrix>
#include <QIcon>
#include <QtMath>
#include <QDir>
#include <QApplication>
#include <QUrl>
#include <QMimeData>

#include "panimage.h"

class UiMainWindow : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(bool HasImage READ HasImage WRITE SetHasImage NOTIFY ImageLoaded)

public:
    explicit UiMainWindow(const QString& fileName = 0, QWidget *parent = 0);

    bool HasImage() const {return m_hasImage;}
    void SetHasImage(bool value);

    PanImage& Image(){return m_PanImage;}
    void SetImage(PanImage& newImage);

    void CreateActions();
    void CreateMenus();
    void CreateTabWidgets();
    void CreatePicDispWidgets(const QString& fileName = 0);
    void CreateCenterWidget(const QString& fileName = 0);
    void CreateStatusBar();
    void CreateGlobalSigSlotLink();
    void CreateMainWindowStyle();
    void CreateImgProcObjs();

signals:
   void ImageChanged();
   void ImageLoaded(bool);
   void MouseOnPicWheeled(int);
   void PicIndexSwitched(int, int);


public slots:
    void OpenPic();
    void NextPic();
    void PrevPic();
    void Save();
    void SaveAs();

    void RotateClkwise();
    void RotateCntrClkwise();
    void MirrorH();
    void MirrorV();

    void ZoomPic(int curValue);
    void ZoomPic();
    void ZoomRateDisp(int value);

    void ShowCurIndexPic();
    void ShowCurPicIndex(int, int);


protected:
    bool eventFilter(QObject* watched, QEvent* event);
    void wheelEvent(QWheelEvent *event);


private:
    // Signals and const values
    bool m_hasImage;

    static const int m_minWidth = 800;
    static const int m_minHeight = 600;

    // Menu action toolbar
    QMenu* m_fileHdlMenu;
    QAction* m_openPic;
    QAction* m_prevPic;
    QAction* m_nextPic;
    QAction* m_saveAs;
    QAction* m_save;
    QMenu* m_picBasicHdlMenu;
    QAction* m_rotateClkwise;
    QAction* m_rotateCntrClkwise;
    QAction* m_mirrorH;
    QAction* m_mirrorV;

    // Tab tool bars
    QWidget* m_centerWidget;
    QTabWidget* m_tabWidget;

    // Status bar
    QStatusBar* m_statusBar;
    QLineEdit* m_zoomRateBox;
    QLineEdit* m_curPicIndexBox;
    QPushButton* m_prevPic2;
    QPushButton* m_nextPic2;

    // Picture display area components
    QScrollArea* m_dispFrame;
    QLabel* m_dispArea;

    // Image to be processed
    PanImage m_PanImage;
    std::vector<PanImage> m_PanImageList;
    QFileInfoList m_curFileList;
    QString m_fileName;
    int m_curFileIndex;
    int m_curFileRange;
    static int const ZOOM_RANGE = 240;
    static int const ZOOM_SAME = 40;
};

#endif // MAINWINDOW_H
