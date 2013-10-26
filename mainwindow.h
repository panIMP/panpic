#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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


class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(bool HasImage READ HasImage WRITE SetHasImage NOTIFY ImageLoaded)
    Q_PROPERTY(QImage Image READ Image WRITE SetImage NOTIFY ImageChanged)


public:
    explicit MainWindow(const QString& fileName = 0, QWidget *parent = 0);

    bool HasImage() const {return m_hasImage;}
    void SetHasImage(bool value);

    QImage* Image() const {return m_Image;}
    void SetImage(const QImage& newImage);

    void CreateActions();
    void CreateMenus();
    void CreateTabWidgets();
    void CreatePicDispWidgets(const QString& fileName = 0);
    void CreateCenterWidget(const QString& fileName = 0);
    void CreateStatusBar();
    void CreateGlobalSigSlotLink();
    void CreateMainWindowStyle();


signals:
   void ImageChanged();
   void ImageLoaded(bool);
   void MouseOnPicWheeled(int);
   void PicIndexSwitched(int, int);


public slots:
    void OpenPic();
    void NextPic();
    void PrevPic();
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
    /* signals and const values*/
    bool m_hasImage;

    static const int m_minWidth = 800;
    static const int m_minHeight = 600;

    /* menu action toolbar */
    QMenu* m_fileHdlMenu;
    QAction* m_openPic;
    QAction* m_prevPic;
    QAction* m_nextPic;
    QAction* m_saveAs;

    QMenu* m_picBasicHdlMenu;
    QAction* m_rotateClkwise;
    QAction* m_rotateCntrClkwise;
    QAction* m_mirrorH;
    QAction* m_mirrorV;

    /* tab tool bars */
    QWidget* m_centerWidget;
    QTabWidget* m_tabWidget;

    /* status bar */
    QStatusBar* m_statusBar;
    QLineEdit* m_zoomRateBox;
    QLineEdit* m_curPicIndexBox;
    QPushButton* m_prevPic2;
    QPushButton* m_nextPic2;

    /* picture display area components */
    QScrollArea* m_dispFrame;
    QLabel* m_dispArea;
    QImage* m_Image;
    static int const ZOOM_RANGE = 240;
    static int const ZOOM_SAME = 120;
    int m_picX;
    int m_picY;

    QFileInfoList m_curFileList;
    QString m_fileName;
    int m_curFileIndex;
    int m_curFileRange;
};

#endif // MAINWINDOW_H
