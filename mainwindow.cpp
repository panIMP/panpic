#include "mainwindow.h"

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


MainWindow::MainWindow(const QString& fileName, QWidget *parent) : QMainWindow(parent)
{
    CreateActions();
    CreateMenus();
    CreateToolBars();
    CreatImageFrameLayout(fileName);
    CreatGlobalSigSlotLink();
}

void MainWindow::CreatImageFrameLayout(const QString& fileName){
    m_dispArea = new QLabel;
    m_dispArea->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    m_dispArea->setAcceptDrops(true);

    if (fileName != 0){
        m_Image = new QImage(fileName);
        SetHasImage(true);
    }else {
        m_Image = new QImage;
        SetHasImage(false);
    }

    m_dispArea->setPixmap(QPixmap::fromImage(*m_Image));
    m_dispArea->setAlignment(Qt::AlignCenter);
    m_dispArea->setAcceptDrops(true);

    m_dispFrame = new QScrollArea;
    m_dispFrame->setAutoFillBackground(true);
    m_dispFrame->setBackgroundRole(QPalette::Light);
    m_dispFrame->setWidgetResizable(true);
    m_dispFrame->setAcceptDrops(true);
    m_dispFrame->setWidget(m_dispArea);

    setCentralWidget(m_dispFrame);
    setAcceptDrops(true);
    setMinimumSize(m_minWidth, m_minHeight);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}


void MainWindow::CreateActions(){
    m_openPic = new QAction(tr("&Open"), this);
    m_openPic->setIcon(QIcon(":/icon/open_pic.ico"));
    m_openPic->setShortcut(QKeySequence::Open);
    m_openPic->setStatusTip(tr("Open an existing picture"));
    connect(m_openPic, SIGNAL(triggered()), this, SLOT(OpenPic()));

    m_nextPic = new QAction(tr("&Next"), this);
    m_nextPic->setIcon(QIcon(":/icon/next_pic.ico"));
    m_nextPic->setStatusTip(tr("Open next picture in current file folder"));
    connect(m_nextPic, SIGNAL(triggered()), this, SLOT(NextPic()));
    connect(this, SIGNAL(ImageLoaded(bool)), m_nextPic, SLOT(setEnabled(bool)));
    m_prevPic = new QAction(tr("&Previous"), this);
    m_prevPic->setIcon(QIcon(":/icon/previous_pic.ico"));
    m_prevPic->setStatusTip(tr("Open previous picture in current file folder"));
    connect(m_prevPic, SIGNAL(triggered()), this, SLOT(PrevPic()));
    connect(this, SIGNAL(ImageLoaded(bool)), m_prevPic, SLOT(setEnabled(bool)));

    m_rotateClkwise = new QAction(tr("&Rotate Clockwise"), this);
    m_rotateClkwise->setIcon(QIcon(":/icon/rotate_clockwise.ico"));
    m_rotateClkwise->setStatusTip("Rotate the picture clockwise");
    connect(m_rotateClkwise, SIGNAL(triggered()), this, SLOT(RotateClkwise()));
    connect(this, SIGNAL(ImageLoaded(bool)), m_rotateClkwise, SLOT(setEnabled(bool)));
    m_rotateCntrClkwise = new QAction(tr("Rotate &Counter Clockwise"), this);
    m_rotateCntrClkwise->setIcon(QIcon(":/icon/rotate_cntrclockwise.ico"));
    m_rotateCntrClkwise->setStatusTip("Rotate the picture counter clockwise");
    connect(m_rotateCntrClkwise, SIGNAL(triggered()), this, SLOT(RotateCntrClkwise()));
    connect(this, SIGNAL(ImageLoaded(bool)), m_rotateCntrClkwise, SLOT(setEnabled(bool)));
    m_mirrorH = new QAction(tr("&Mirror Horizontally"), this);
    m_mirrorH->setIcon(QIcon(":/icon/mirror_horizontally"));
    m_mirrorH->setStatusTip("Mirror the picture horizontally");
    connect(m_mirrorH, SIGNAL(triggered()), this, SLOT(MirrorH()));
    connect(this, SIGNAL(ImageLoaded(bool)), m_mirrorH, SLOT(setEnabled(bool)));
    m_mirrorV = new QAction(tr("Mirror &Vertically"), this);
    m_mirrorV->setIcon(QIcon(":/icon/mirror_vertically"));
    m_mirrorV->setStatusTip("Mirror the picture vertically");
    connect(m_mirrorV, SIGNAL(triggered()), this, SLOT(MirrorV()));
    connect(this, SIGNAL(ImageLoaded(bool)), m_mirrorV, SLOT(setEnabled(bool)));
}


void MainWindow::CreateMenus(){
    m_fileHdlMenu = menuBar()->addMenu(tr("&File"));

    m_fileHdlMenu->addAction(m_openPic);
    m_fileHdlMenu->addAction(m_nextPic);
    m_fileHdlMenu->addAction(m_prevPic);

    m_imageHdlMenu = menuBar()->addMenu(tr("&Handle"));
    m_imageHdlMenu->addAction(m_rotateClkwise);
    m_imageHdlMenu->addAction(m_rotateCntrClkwise);
    m_imageHdlMenu->addAction(m_mirrorH);
    m_imageHdlMenu->addAction(m_mirrorV);
}

void MainWindow::CreateToolBars(){
    m_quickHand = new QuickHandWidget;

    // pic has been loaded --> enable quickHand widget
    connect(this, SIGNAL(ImageLoaded(bool)), m_quickHand, SLOT(setEnabled(bool)));
    // pic has been indexed --> quickHand index widget disp value
    connect(this, SIGNAL(CurPicIndex(int,int)), m_quickHand, SLOT(curPicIndexDisp(int,int)));
    // pic index has been edited --> show cur index pic
    connect(m_quickHand, SIGNAL(picIndexChanged()), this, SLOT(ShowCurIndexPic()));
    // slider in quick hand zoom --> pic zoom
    connect(m_quickHand, SIGNAL(zoom(int)), this, SLOT(ZoomPic(int)));
    // wheel change the pic size --> zoom slider change value --> zoom rate box change value
    connect(this, SIGNAL(CurWheelDistance(int)), m_quickHand, SLOT(zoomSliderMove(int)));

    m_ToolBar = addToolBar(tr("&Quick Hand"));
    m_ToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    m_ToolBar->setAllowedAreas(Qt::BottomToolBarArea);

    m_ToolBar->addWidget(m_quickHand);
    m_ToolBar->addAction(m_prevPic);
    m_ToolBar->addAction(m_nextPic);
    m_ToolBar->addAction(m_rotateClkwise);
    m_ToolBar->addAction(m_rotateCntrClkwise);
    m_ToolBar->addAction(m_mirrorH);
    m_ToolBar->addAction(m_mirrorV);
}

void MainWindow::CreatGlobalSigSlotLink(){
    connect(this, SIGNAL(CurWheelDistance(int)), this, SLOT(ZoomPic(int)));
}

/*
 *  Action slot functions
 */
void MainWindow::OpenPic(){
    QString selectedFilter = tr("ALL(*.*)");
    m_fileName = QFileDialog::getOpenFileName(this,tr("Open File"), ".",
                                              tr("JPEG(*.jpg *.jpeg);; BMP(*.bmp);;"\
                                                 "PNG(*.png);;TIFF(*.tif)"\
                                                 ";;GIF(*.gif);; ICO(*.ico);; ALL(*.*)"
                                                 ),
                                              &selectedFilter);
    if (m_fileName != NULL){
        SetImage(QImage(m_fileName));
        SetHasImage(true);
    }

    QDir dir;
    dir.setPath(QFileInfo(m_fileName).dir().absolutePath());
    QStringList filter;
    filter<<"*.jpg"<<"*.jpeg"<<"*.bmp"<<"*.png"<<"*gif" <<"*.ico"<<"*.tif";
    dir.setNameFilters(filter);
    m_curFileList = dir.entryInfoList();
    m_curFileIndex = m_curFileList.indexOf(QFileInfo(m_fileName));
    m_curFileRange = m_curFileList.size();
    emit(CurPicIndex(m_curFileIndex, m_curFileRange));
}

void MainWindow::NextPic(){
    m_curFileIndex ++;
    if (m_curFileIndex < m_curFileRange){
        QString curfileName = m_curFileList.at(m_curFileIndex).absoluteFilePath();
        if (curfileName != NULL){
            SetImage(QImage(curfileName));
            SetHasImage(true);
        }
    }else {
        m_curFileIndex --;
    }

    emit(CurPicIndex(m_curFileIndex, m_curFileRange));
}

void MainWindow::PrevPic(){
    m_curFileIndex --;
    if (m_curFileIndex >= 0){
        QString curfileName = m_curFileList.at(m_curFileIndex).absoluteFilePath();
        if (curfileName != NULL){
            SetImage(QImage(curfileName));
            SetHasImage(true);
        }
    }else {
        m_curFileIndex ++;
    }

    emit(CurPicIndex(m_curFileIndex, m_curFileRange));
}

void MainWindow::RotateClkwise(){
    QMatrix matrix;
    matrix.rotate(90);

    SetImage(m_Image->transformed(matrix));
}

void MainWindow::RotateCntrClkwise(){
    QMatrix matrix;
    matrix.rotate(-90);

    SetImage(m_Image->transformed(matrix));
}

void MainWindow::MirrorH(){
    SetImage(m_Image->mirrored(true, false));
}

void MainWindow::MirrorV(){
    SetImage(m_Image->mirrored(false, true));
}

void MainWindow::ZoomPic(int curValue){
    int curWidth;
    if (curValue < QuickHandWidget::ZOOM_SAME){
        curWidth = m_Image->width() * curValue / QuickHandWidget::ZOOM_SAME;
    }else {
        curWidth = m_Image->width() * (curValue*curValue)
                            / (QuickHandWidget::ZOOM_SAME * QuickHandWidget::ZOOM_SAME);
    }
    QImage curImg = m_Image->scaledToWidth(curWidth);

    m_dispArea->setPixmap(QPixmap::fromImage(curImg));
    update();
    updateGeometry();
}

void MainWindow::ShowCurIndexPic(){
    QString str = m_quickHand->getCurPicIndex();
    QStringList strList = str.split('/');
    int index;
    // if lineEdit content is "/33" sort like this, strList will become {"","33"}
    if (strList[0] == ""){
        index = m_curFileIndex;
    }else {
        index = strList[0].toInt() - 1;
    }
    m_quickHand->curPicIndexDisp(index, m_curFileRange);
    QString curfileName = m_curFileList.at(index).absoluteFilePath();
    if (curfileName != NULL){
        SetImage(QImage(curfileName));
        SetHasImage(true);
    }
}


/*
 *  general public functions
 */
void MainWindow::SetHasImage(bool value){
    m_hasImage = value;
    emit(ImageLoaded(value));
}

void MainWindow::SetImage(const QImage& newImage){
    if (! m_Image->isNull()){
        if (newImage != *m_Image){
            delete m_Image;
            emit(ImageChanged());
        }else {
            return;
        }
    }
    m_Image = new QImage(newImage);
    m_dispArea->setPixmap(QPixmap::fromImage(*m_Image));
    update();
    updateGeometry();
}

/*
 *  protected implemented virtual methods
 */
bool MainWindow::eventFilter(QObject* watched, QEvent* event){
    if (watched == this){
        if (event->type() == QEvent::DragEnter){
            QDragEnterEvent* dragEnter = dynamic_cast<QDragEnterEvent*>(event);
            dragEnter->acceptProposedAction();
            return true;
        } else if (event->type() == QEvent::Drop){
            QDropEvent* drop = dynamic_cast<QDropEvent*>(event);
            QList<QUrl> urls = drop->mimeData()->urls();
            if (urls.isEmpty()){
                return true;
            }
            QString path = urls.first().toLocalFile();
            QImage* loadImage = new QImage(path);
            if (! loadImage->isNull()){
                SetImage(*loadImage);
            }
            return true;
        }
    }

    return QWidget::eventFilter(watched, event);
}

void MainWindow::wheelEvent(QWheelEvent *event){
    static int wheeledDistance = 0;
    if (QApplication::keyboardModifiers() == Qt::ControlModifier){
        wheeledDistance += (event->angleDelta() / 20).y();
        if (wheeledDistance > QuickHandWidget::ZOOM_SAME){
            wheeledDistance = QuickHandWidget::ZOOM_SAME;
        }else if(wheeledDistance < -QuickHandWidget::ZOOM_SAME){
            wheeledDistance = -QuickHandWidget::ZOOM_SAME;
        }else {
            emit(CurWheelDistance(wheeledDistance + QuickHandWidget::ZOOM_SAME));
        }
    }
}















