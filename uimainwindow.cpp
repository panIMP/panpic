#include "uimainwindow.h"


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
    CreateStatusBar();
    CreateCenterWidget(fileName);
    CreateGlobalSigSlotLink();
    CreateMainWindowStyle();
    CreateOthers();
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
    m_tab1 = new QWidget;
    m_openPic = new QPushButton(QIcon(":/icon/open_pic.ico"), "", this);
    connect(m_openPic, SIGNAL(clicked()), this, SLOT(OpenPic()));
    m_save = new QPushButton(QIcon(":/icon/save.ico"), "", this);
    connect(m_save, SIGNAL(clicked()), this, SLOT(Save()));
    connect(this, SIGNAL(ImageLoaded(bool)), m_save, SLOT(setEnabled(bool)));
    m_saveAs = new QPushButton(QIcon(":/icon/saveAs.ico"), "", this);
    connect(m_saveAs, SIGNAL(clicked()), this, SLOT(SaveAs()));
    connect(this, SIGNAL(ImageLoaded(bool)), m_saveAs, SLOT(setEnabled(bool)));
    QHBoxLayout* hLay1 = new QHBoxLayout;
    hLay1->addWidget(m_openPic);
    hLay1->addWidget(m_save);
    hLay1->addWidget(m_saveAs);
    hLay1->addStretch();
    m_tab1->setLayout(hLay1);

    m_tab2 = new QWidget;
    QHBoxLayout* hLay2 = new QHBoxLayout;
    m_rotateClkwise = new QPushButton(QIcon(":/icon/rotate_clockwise.ico"), "", this);
    connect(m_rotateClkwise, SIGNAL(clicked()), this, SLOT(RotateClkwise()));
    m_rotateCntrClkwise = new QPushButton(QIcon(":/icon/rotate_cntrclockwise.ico"), "", this);
    connect(m_rotateCntrClkwise, SIGNAL(clicked()), this, SLOT(RotateCntrClkwise()));
    m_mirrorH = new QPushButton(QIcon(":/icon/mirror_horizontally.ico"), "", this);
    connect(m_mirrorH, SIGNAL(clicked()), this, SLOT(MirrorH()));
    m_mirrorV = new QPushButton(QIcon(":/icon/mirror_vertically.ico"), "", this);
    connect(m_mirrorV, SIGNAL(clicked()), this, SLOT(MirrorV()));
    connect(this, SIGNAL(ImageLoaded(bool)), m_tab2, SLOT(setEnabled(bool)));
    hLay2->addWidget(m_rotateClkwise);
    hLay2->addWidget(m_rotateCntrClkwise);
    hLay2->addWidget(m_mirrorH);
    hLay2->addWidget(m_mirrorV);
    hLay2->addStretch();
    m_tab2->setLayout(hLay2);

    m_tab3 = new QWidget;
    QHBoxLayout* hLay3 = new QHBoxLayout;
    m_dispHist = new QPushButton(QIcon(":/icon/hist.ico"), "", this);
    connect(m_dispHist, SIGNAL(clicked()), this, SLOT(CreateHistDialog()));
    m_equalizeHist = new QPushButton(QIcon(":/icon/equalizehist.ico"), "", this);
    connect(m_equalizeHist, SIGNAL(clicked()), this, SLOT(EqualizeHist()));
    connect(this, SIGNAL(ImageLoaded(bool)), m_tab3, SLOT(setEnabled(bool)));
    hLay3->addWidget(m_dispHist);
    hLay3->addWidget(m_equalizeHist);
    hLay3->addStretch();
    m_tab3->setLayout(hLay3);

    m_tabWidget = new QTabWidget(this);
    m_tabWidget->addTab(m_tab1, QIcon(":/icon/tab1.ico"), "File");
    m_tabWidget->addTab(m_tab2, QIcon(":/icon/tab2.ico"), "Shift");
    m_tabWidget->addTab(m_tab3, QIcon(":/icon/tab2.ico"), "Pixel");
    m_tabWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
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
        m_dispArea->setPixmap(QPixmap::fromImage(m_PanImage.PanImage2QImage()));
        SetHasImage(true);
    }
    else {
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

    m_centerSplitter = new QSplitter(Qt::Vertical);
    m_centerSplitter->addWidget(m_tabWidget);
    m_centerSplitter->addWidget(m_dispFrame);
    m_centerSplitter->setStretchFactor(1,1);

    setCentralWidget(m_centerSplitter);
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
    // \d should be set as \\
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
Fuction:        CreateOthers()

Description:    Create all the other image processing related objects

Input:          None

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::CreateOthers(){
    m_curFileIndex = 0;
    m_curFileRange = 0;
}


/*---------------------------------------------------------------------
Fuction:        OpenPic()

Description:    Slot for "m_openPic" action

Input:          None

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::OpenPic(){
    QString selectedFilter = tr("JPEG(*.jpg &.jpeg)");
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
    }
    else {
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
    }
    else {
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
    QString selectedFilter = tr("JPEG(*.jpg *.jpeg)");
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
    int channelNum = m_PanImage.GetMat().channels();
    if (channelNum == 1){
        m_dispArea->setPixmap(QPixmap::
                              fromImage(m_PanImage.PanImage2QImage().
                              convertToFormat(QImage::Format_RGB888).
                              scaledToWidth(curWidth)));
    }
    else if(channelNum == 3) {
        m_dispArea->setPixmap(QPixmap::fromImage(m_PanImage.PanImage2QImage().scaledToWidth(curWidth)));
    }
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
    m_dispArea->setPixmap(QPixmap::fromImage(m_PanImage.PanImage2QImage().scaledToWidth(curWidth)));
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


void UiMainWindow::EqualizeHist(){
    PanImageHistProc::GetInstance()->HistEqalization(m_PanImage);
    SetImage(m_PanImage);
}


void UiMainWindow::CreateHistDialog(){
    UiHistDialog* hist = new UiHistDialog(m_PanImage, m_fileName);
    hist->show();
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
    m_dispArea->setPixmap(QPixmap::fromImage(m_PanImage.PanImage2QImage()));
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
        }
        else if (event->type() == QEvent::Drop){
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
        if (wheeledDistance <= -ZOOM_SAME){
            wheeledDistance = -ZOOM_SAME;
        }
        emit(MouseOnPicWheeled(wheeledDistance + ZOOM_SAME));
    }
}

