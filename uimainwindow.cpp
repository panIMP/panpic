#include "uimainwindow.h"
#include "panimage.h"
#include "panimageio.h"
#include "panimageshift.h"


/*---------------------------------------------------------------------
Fuction:        MainWindow(const QString& fileName, QWidget *parent)

Description:    1. Creat mainwindow
                2. Careful about the sub function calling order or some
                   operation may be used before its calling object's initiation

Input:          None

Output:         None
----------------------------------------------------------------------*/
UiMainWindow::UiMainWindow(const QString& fileName, QWidget *parent) : QMainWindow(parent)
{
    CreateActions();
    CreateMenus();
    CreateStatusBar();
    CreateCenterWidget(fileName);
    CreateGlobalSigSlotLink();
    CreateMainWindowStyle();
    CreateImgProcObjs();
}


/*---------------------------------------------------------------------
Fuction:        CreateActions()

Description:    1. Creat all the actions in the mainwidow
                2. Bond action signals with their functional slots

Input:          None

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::CreateActions(){
    /*-------------------------------------------------------------
    file handle menu contained actions
    -------------------------------------------------------------*/
    m_openPic = new QAction(tr("&Open"), this);
    m_openPic->setIcon(QIcon(":/icon/open_pic.ico"));
    m_openPic->setShortcut(QKeySequence::Open);
    m_openPic->setStatusTip(tr("Open an existing picture"));
    // action --> correspond slot
    connect(m_openPic, SIGNAL(triggered()), this, SLOT(OpenPic()));
    m_nextPic = new QAction(tr("&Next"), this);
    m_nextPic->setIcon(QIcon(":/icon/next_pic.ico"));
    m_nextPic->setStatusTip(tr("Open next picture in current file folder"));
    connect(m_nextPic, SIGNAL(triggered()), this, SLOT(NextPic()));
    // only after picture loaded can this action be enabled
    connect(this, SIGNAL(ImageLoaded(bool)), m_nextPic, SLOT(setEnabled(bool)));
    m_prevPic = new QAction(tr("&Previous"), this);
    m_prevPic->setIcon(QIcon(":/icon/previous_pic.ico"));
    m_prevPic->setStatusTip(tr("Open previous picture in current file folder"));
    connect(m_prevPic, SIGNAL(triggered()), this, SLOT(PrevPic()));
    connect(this, SIGNAL(ImageLoaded(bool)), m_prevPic, SLOT(setEnabled(bool)));
    m_save = new QAction(tr("&Save"), this);
    m_save->setIcon(QIcon(":/icon/save.ico"));
    m_save->setStatusTip("Save the initial picture");
    connect(m_save, SIGNAL(triggered()), this, SLOT(Save()));
    connect(this, SIGNAL(ImageLoaded(bool)), m_save, SLOT(setEnabled(bool)));
    m_saveAs = new QAction(tr("Save &As"), this);
    m_saveAs->setIcon(QIcon(":/icon/saveAs.ico"));
    m_saveAs->setStatusTip("Save the picture apart from the initial picture");
    connect(m_saveAs, SIGNAL(triggered()), this, SLOT(SaveAs()));
    connect(this, SIGNAL(ImageLoaded(bool)), m_saveAs, SLOT(setEnabled(bool)));

    /*-------------------------------------------------------------
    picture basic handle menu contained actions
    -------------------------------------------------------------*/
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


/*---------------------------------------------------------------------
Fuction:        CreateMenus()

Description:    1. Creat all the menus and submenus... in the mainwidow
                2. Bond menus with actions

Input:          None

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::CreateMenus(){
    // file handle menu
    m_fileHdlMenu = menuBar()->addMenu(tr("&File"));
    m_fileHdlMenu->addAction(m_openPic);
    m_fileHdlMenu->addSeparator();
    m_fileHdlMenu->addAction(m_nextPic);
    m_fileHdlMenu->addAction(m_prevPic);
    m_fileHdlMenu->addSeparator();
    m_fileHdlMenu->addAction(m_save);
    m_fileHdlMenu->addAction(m_saveAs);

    // picture basic handle menu
    m_picBasicHdlMenu = menuBar()->addMenu(tr("&Handle"));
    m_picBasicHdlMenu->addAction(m_rotateClkwise);
    m_picBasicHdlMenu->addAction(m_rotateCntrClkwise);
    m_picBasicHdlMenu->addAction(m_mirrorH);
    m_picBasicHdlMenu->addAction(m_mirrorV);
}


/*---------------------------------------------------------------------
Fuction:        CreateTabWidgets()

Description:    1. Creat all the tabWidget in the mainwidow center widget
                2. Use tabWidget as a flexibale multiply of toolbars
                3. Set components and layouts of all tabs
                4. Add each tab to the tabWidget

Input:          None

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::CreateTabWidgets(){
    QWidget* m_tab1 = new QWidget;
    QHBoxLayout* hLay1 = new QHBoxLayout;

    m_tab1->setLayout(hLay1);

    m_tabWidget = new QTabWidget(this);
    m_tabWidget->addTab(m_tab1, QIcon(":/icon/m_tab1.png"), "quick handles");
    m_tabWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    connect(this, SIGNAL(ImageLoaded(bool)), m_tabWidget, SLOT(setEnabled(bool)));
}


/*---------------------------------------------------------------------
Fuction:        CreatePicDispWidgets(const QString &fileName)

Description:    1. Creat picture display area in the mainwidow center widget
                2. Init image file to display

Input:          File path of the image file to display

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::CreatePicDispWidgets(const QString &fileName){
    m_dispArea = new QLabel;
    m_dispArea->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    m_dispArea->setAlignment(Qt::AlignCenter);
    m_dispArea->setAcceptDrops(true);

    if (fileName != 0){
        m_PanImage = PanImageIO::GetInstance()->ReadPanImage(fileName);
        m_dispArea->setPixmap(QPixmap::fromImage(PanImageShift::GetInstance()->CvImage2QImage(m_PanImage)));
        SetHasImage(true);
    }else {
        m_PanImage.GetMat().create(0, 0, CV_8UC3);
        SetHasImage(false);
    }

    m_dispFrame = new QScrollArea;
    m_dispFrame->setAutoFillBackground(true);
    m_dispFrame->setBackgroundRole(QPalette::Light);
    m_dispFrame->setWidgetResizable(true);
    m_dispFrame->setAcceptDrops(true);
    m_dispFrame->setWidget(m_dispArea);
}


/*---------------------------------------------------------------------
Fuction:        CreatCenterWidget(const QString& fileName)

Description:    1. Creat the layout of the center widget of mainwindow
                2. transfer the file path parameter

Input:          File path of the image file to display

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::CreateCenterWidget(const QString& fileName){
    CreateTabWidgets();
    CreatePicDispWidgets(fileName);

    QVBoxLayout* vLay = new QVBoxLayout;
    vLay->addWidget(m_tabWidget);
    vLay->addWidget(m_dispFrame);

    m_centerWidget = new QWidget;
    m_centerWidget->setAcceptDrops(true);
    m_centerWidget->setLayout(vLay);

    setCentralWidget(m_centerWidget);
    setAcceptDrops(true);
    setMinimumSize(m_minWidth, m_minHeight);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}


/*---------------------------------------------------------------------
Fuction:        CreatStatusBar()

Description:    1. Creat the status bar of mainwindow
                2. Set components and layout of statusbar

Input:          None

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::CreateStatusBar(){
    m_zoomRateBox = new QLineEdit(this);
    m_zoomRateBox->setText("100%");
    m_zoomRateBox->setMaximumWidth(40);
    m_zoomRateBox->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    // use regular expression to restrict the input to be like 'dd%'
    QRegExp zoomRegexp("[0-9]+%$");
    QValidator* zoomValidator = new QRegExpValidator(zoomRegexp, m_zoomRateBox);
    m_zoomRateBox->setValidator(zoomValidator);
    // zoom rate box content edited --> zoom pic according to the new content
    connect(m_zoomRateBox, SIGNAL(returnPressed()), this, SLOT(ZoomPic()));

    m_curPicIndexBox = new QLineEdit(this);
    m_curPicIndexBox->setText("0/0");
    m_curPicIndexBox->setMaximumWidth(50);
    m_curPicIndexBox->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    // use regular expression to restrict the input to be like 'dd/dd'
    // \d should be set as \\d
    // The C++ compiler transforms backslashes in strings. To include a \ in a regexp,
    // enter it twice, i.e. \\.
    // To match the backslash character itself, enter it four times, i.e. \\\\.
    QRegExp picIndexRegexp("^\\d*/\\d*$");
    QValidator* picIndexValidator = new QRegExpValidator(picIndexRegexp, m_curPicIndexBox);
    m_curPicIndexBox->setValidator(picIndexValidator);
    // pic index box content edited --> switch cur displaying picture
    connect(m_curPicIndexBox, SIGNAL(returnPressed()), this, SLOT(ShowCurIndexPic()));

    m_prevPic2 = new QPushButton(QIcon(":/icon/previous_pic.ico"),"", this);
    connect(m_prevPic2, SIGNAL(clicked()), this, SLOT(PrevPic()));
    m_nextPic2 = new QPushButton(QIcon(":/icon/next_pic.ico"),"", this);
    connect(m_nextPic2, SIGNAL(clicked()), this, SLOT(NextPic()));

    m_statusBar = statusBar();
    m_statusBar->addWidget(m_prevPic2);
    m_statusBar->addWidget(m_curPicIndexBox);
    m_statusBar->addWidget(m_nextPic2);
    m_statusBar->addWidget(m_zoomRateBox);
    connect(this, SIGNAL(ImageLoaded(bool)), m_statusBar, SLOT(setEnabled(bool)));

}


/*---------------------------------------------------------------------
Fuction:        CreatGlobalSigSlotLink()

Description:    Link global signals and slots

Input:          None

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::CreateGlobalSigSlotLink(){
    // mouse wheeled -- > zoom pic & change zoom rate box
    connect(this, SIGNAL(MouseOnPicWheeled(int)), this, SLOT(ZoomPic(int)));
    connect(this, SIGNAL(MouseOnPicWheeled(int)), this, SLOT(ZoomRateDisp(int)));

    // "next" action or "previous" action pushed --> change pic index box content;
    connect(this, SIGNAL(PicIndexSwitched(int,int)), this, SLOT(ShowCurPicIndex(int,int)));
}


/*---------------------------------------------------------------------
Fuction:        CreateMainWindowStyle()

Description:    Create mainwindow style -- size, accepts, title...

Input:          None

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::CreateMainWindowStyle(){
    setAcceptDrops(true);
}


/*---------------------------------------------------------------------
Fuction:        CreateImgProcObjs()

Description:    Create all the image processing related objects that operate
                all the imgproc algorithm tasks in the software

Input:          None

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::CreateImgProcObjs(){

}


/*---------------------------------------------------------------------
Fuction:        OpenPic()

Description:    Slot for "m_openPic" action

Input:          None

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::OpenPic(){
    QString selectedFilter = tr("PNG(*.png)");
    m_fileName = QFileDialog::getOpenFileName(this,
                                              tr("Open File"),
                                              "../",
                                              tr("JPEG(*.jpg *.jpeg);; BMP(*.bmp);;"\
                                                 "PNG(*.png);;TIFF(*.tif)"\
                                                 ";;GIF(*.gif);; ICO(*.ico);; ALL(*.*)"
                                                 ),
                                              &selectedFilter);
    if (m_fileName != NULL){
        SetImage(PanImageIO::GetInstance()->ReadPanImage(m_fileName));
        SetHasImage(true);
    }

    // once open the picture, get its fileindex and filerange
    QDir dir;
    dir.setPath(QFileInfo(m_fileName).dir().absolutePath());
    QStringList filter;
    filter<<"*.jpg"<<"*.jpeg"<<"*.bmp"<<"*.png"<<"*gif" <<"*.ico"<<"*.tif";
    dir.setNameFilters(filter);
    m_curFileList = dir.entryInfoList();
    m_curFileIndex = m_curFileList.indexOf(QFileInfo(m_fileName));
    m_curFileRange = m_curFileList.size();

    // emit the signal that fileindex and filerange has changed
    emit(PicIndexSwitched(m_curFileIndex, m_curFileRange));
}


/*---------------------------------------------------------------------
Fuction:        PrevPic()

Description:    Slot for "m_nextPic" action

Input:          None

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::PrevPic(){
    m_curFileIndex --;
    if (m_curFileIndex >= 0){
        QString curfileName = m_curFileList.at(m_curFileIndex).absoluteFilePath();
        if (curfileName != NULL){
            m_fileName = curfileName;
            SetImage(PanImageIO::GetInstance()->ReadPanImage(m_fileName));
            SetHasImage(true);
        }
    }else {
        m_curFileIndex ++;
    }

    // emit the signal that fileindex and filerange has changed
    emit(PicIndexSwitched(m_curFileIndex, m_curFileRange));
}


/*---------------------------------------------------------------------
Fuction:        NextPic()

Description:    Slot for "m_nextPic" action

Input:          None

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::NextPic(){
    m_curFileIndex ++;
    if (m_curFileIndex < m_curFileRange){
        QString curfileName = m_curFileList.at(m_curFileIndex).absoluteFilePath();
        if (curfileName != NULL){
            m_fileName = curfileName;
            SetImage(PanImageIO::GetInstance()->ReadPanImage(m_fileName));
            SetHasImage(true);
        }
    }else {
        m_curFileIndex --;
    }

    // emit the signal that fileindex and filerange has changed
    emit(PicIndexSwitched(m_curFileIndex, m_curFileRange));
}


/*---------------------------------------------------------------------
Fuction:        Save()

Description:    Slot for "m_save" action

Input:          None

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::Save(){
    cv::cvtColor(m_PanImage.GetMat(), m_PanImage.GetMat(), CV_RGB2BGR);
    PanImageIO::GetInstance()->SavePanImage(m_PanImage, QFileInfo(m_fileName).absoluteFilePath());
    setWindowModified(false);
    setWindowTitle("panpic - " + QFileInfo(m_fileName).fileName());
    setWindowModified(false);
}


/*---------------------------------------------------------------------
Fuction:        SaveAs()

Description:    Slot for "m_saveAs" action

Input:          None

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::SaveAs(){
    QString selectedFilter = tr("PNG(*.png)");
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Open File"),
                                                    "../",
                                                    tr("JPEG(*.jpg *.jpeg);; BMP(*.bmp);;"\
                                                       "PNG(*.png);;TIFF(*.tif)"\
                                                       ";;GIF(*.gif);; ICO(*.ico);; ALL(*.*)"
                                                       ),
                                                    &selectedFilter);
    if (fileName != NULL){
        PanImageIO::GetInstance()->SavePanImage(m_PanImage, QFileInfo(fileName).absoluteFilePath());
        setWindowModified(false);
        setWindowTitle("panpic - " + QFileInfo(fileName).fileName());
    }
    setWindowModified(false);
}


/*---------------------------------------------------------------------
Fuction:        RotateClkwise()

Description:    Slot for "m_rotateClkwise" action

Input:          None

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::RotateClkwise(){
    PanImageShift::GetInstance()->RotateClockWise(m_PanImage);
    SetImage(m_PanImage);
}


/*---------------------------------------------------------------------
Fuction:        RotateCntrClkwise()

Description:    Slot for "m_rotateCntrClkwise" action

Input:          None

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::RotateCntrClkwise(){
    PanImageShift::GetInstance()->RotateCntrClockWise(m_PanImage);
    SetImage(m_PanImage);
}


/*---------------------------------------------------------------------
Fuction:        MirrorH()

Description:    Slot for "m_mirrorH" action

Input:          None

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::MirrorH(){
    PanImageShift::GetInstance()->MirrorH(m_PanImage);
    SetImage(m_PanImage);
}


/*---------------------------------------------------------------------
Fuction:        MirrorV()

Description:    Slot for "m_mirrorV" action

Input:          None

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::MirrorV(){
    PanImageShift::GetInstance()->MirrorV(m_PanImage);
    SetImage(m_PanImage);
}


/*---------------------------------------------------------------------
Fuction:        ZoomPic(int curValue)

Description:    SLOT -- zoom in or zoom out the picture
                Signals that satisfied following two requirements should
                link to this SLOT:
                1. meant to zoom the picture
                2. can transfer the relative value of zoomed piture while
                   set original picture as ZOOM_SAME

Input:          Relative value of zoomed piture by comparison of border length

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::ZoomPic(int curValue){
    int curWidth = m_PanImage.GetMat().cols * curValue / ZOOM_SAME;
    m_dispArea->setPixmap(QPixmap::fromImage(PanImageShift::
                                             GetInstance()->
                                             CvImage2QImage(m_PanImage).
                                             scaledToWidth(curWidth)));
    update();
    updateGeometry();
}


/*---------------------------------------------------------------------
Fuction:        ZoomPic()

Description:    SLOT -- zoom in or zoom out the picture
                Signals that satisfied following two requirements should
                link to this SLOT:
                1. meant to zoom the picture

Input:          None

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::ZoomPic(){
    QString tmpStr = QString(m_zoomRateBox->text());
    tmpStr.chop(1);
    float value = tmpStr.toFloat() / 100.0;
    int curWidth = static_cast<int>(value * float(m_PanImage.GetMat().cols));
    m_dispArea->setPixmap(QPixmap::fromImage(PanImageShift::
                                             GetInstance()->
                                             CvImage2QImage(m_PanImage).
                                             scaledToWidth(curWidth)));
    update();
    updateGeometry();
}


/*---------------------------------------------------------------------
Fuction:        ZoomRateDisp()

Description:    SLOT -- change the zoom rate value in the zoom rate box
                        accrording to the relative value

Input:          Relative value

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::ZoomRateDisp(int value){
    int rate = static_cast<int>(float(value) / float(ZOOM_SAME) * 100.0);
    m_zoomRateBox->setText(QString("%1%").arg(rate));
}


/*---------------------------------------------------------------------
Fuction:        ShowCurIndexPic()

Description:    SLOT -- display piture of current index in the frame

Input:          None

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::ShowCurIndexPic(){
    QString str = m_curPicIndexBox->text();
    QStringList strList = str.split('/');

    // if lineEdit content is "/33" sort like this, strList will become {"","33"}
    int index;
    if (strList[0] == ""){
        index = m_curFileIndex;
    }else {
        index = strList[0].toInt() - 1;
    }

    m_curFileIndex = index;
    m_curPicIndexBox->setText(QString("%1/%2").arg(index + 1).arg(m_curFileRange));

    QString curfileName = m_curFileList.at(index).absoluteFilePath();
    if (curfileName != NULL){
        m_fileName = curfileName;
        SetImage(PanImageIO::GetInstance()->ReadPanImage(m_fileName));
        SetHasImage(true);
    }
}


/*---------------------------------------------------------------------
Fuction:        ShowCurPicIndex(int indexVal, int rangeVal)

Description:    SLOT -- show current picture index in current folder

Input:          indexVal -- picture index in picture file list
                rangeVal -- picture file list element num

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::ShowCurPicIndex(int indexVal, int rangeVal){
    m_curPicIndexBox->setText(QString("%1/%2").arg(indexVal + 1).arg(rangeVal));
}


/*---------------------------------------------------------------------
Fuction:        SetHasImage(bool value)

Description:    Set function of property -- "m_hasImage"(bool)

Input:          True or false

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::SetHasImage(bool value){
    m_hasImage = value;
    emit(ImageLoaded(value));
}


/*---------------------------------------------------------------------
Fuction:        SetImage(const QImage& newImage)

Description:    1. Set function of property -- "m_Image"(QImage*)
                2. Update the display after setting the image

Input:          cv::Mat instance

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::SetImage(PanImage& newImage){
    m_PanImage = newImage;
    m_dispArea->setPixmap(QPixmap::fromImage(PanImageShift::GetInstance()->CvImage2QImage(m_PanImage)));
    emit(ImageChanged());
    setWindowTitle("panpic - " + QFileInfo(m_fileName).fileName());
    update();
    updateGeometry();
}


/*---------------------------------------------------------------------
Fuction:        Overload -- eventFilter(QObject* watched, QEvent* event)

Description:    1. To implement of dragging and placing image on frame
                   through mouse

Input:          1. QObject* of the operation upon
                2. Event that trigged

Output:         True or False
----------------------------------------------------------------------*/
bool UiMainWindow::eventFilter(QObject* watched, QEvent* event){
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
            if (!path.isNull()){
                SetImage(PanImageIO::GetInstance()->ReadPanImage(path));
            }
            return true;
        }
    }

    return QWidget::eventFilter(watched, event);
}


/*---------------------------------------------------------------------
Fuction:        Overload -- wheelEvent(QWheelEvent *event)

Description:    1. To implement of mouse wheel zooming -- to picture

Input:          1. Event that trigged

Output:         True or False
----------------------------------------------------------------------*/
void UiMainWindow::wheelEvent(QWheelEvent *event){
    static int wheeledDistance = 0;
    if (QApplication::keyboardModifiers() == Qt::ControlModifier){
        wheeledDistance += (event->angleDelta() / 20).y();

        if(wheeledDistance <= -ZOOM_SAME){
            wheeledDistance = -ZOOM_SAME;
        }
        emit(MouseOnPicWheeled(wheeledDistance + ZOOM_SAME));
    }
}

