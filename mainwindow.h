#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QScrollArea>
#include <QToolBar>
#include <QFileInfoList>
#include <QObject>
#include <QWheelEvent>

#include "quickhandwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(bool HasImage READ HasImage WRITE SetHasImage NOTIFY ImageLoaded)
    Q_PROPERTY(QImage Image READ Image WRITE SetImage NOTIFY ImageChanged)


public:
    explicit MainWindow(const QString& m_fileName = 0, QWidget *parent = 0);

    bool HasImage() const {return m_hasImage;}
    void SetHasImage(bool value);

    QImage* Image() const {return m_Image;}
    void SetImage(const QImage& newImage);

    void CreateActions();
    void CreateMenus();
    void CreateToolBars();
    void CreatImageFrameLayout(const QString& m_fileName = 0);
    void CreatGlobalSigSlotLink();


signals:
   void ImageChanged();
   void ImageLoaded(bool);
   void CurPicIndex(int, int);
   void CurWheelDistance(int);


public slots:
    void OpenPic();
    void NextPic();
    void PrevPic();

    void RotateClkwise();
    void RotateCntrClkwise();
    void MirrorH();
    void MirrorV();

    void ZoomPic(int curValue);
    void ShowCurIndexPic();


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
    QAction* m_nextPic;
    QAction* m_prevPic;

    QMenu* m_imageHdlMenu;
    QAction* m_rotateClkwise;
    QAction* m_rotateCntrClkwise;
    QAction* m_mirrorH;
    QAction* m_mirrorV;

    /* tool bars */
    QToolBar* m_ToolBar;
    QuickHandWidget* m_quickHand;

    /* picture display area components */
    QScrollArea* m_dispFrame;
    QLabel* m_dispArea;
    QImage* m_Image;
    QFileInfoList m_curFileList;
    QString m_fileName;
    int m_curFileIndex;
    int m_curFileRange;
};

#endif // MAINWINDOW_H
