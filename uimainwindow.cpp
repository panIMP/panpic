#include "uimainwindow.h"

_Pan_Circle bigCircle;
_Pan_Circle smallCircle;


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
	InitGlobalVariables();
	CreateCenterWidget(fileName);
	CreateStatusBar();
	CreateGlobalSigSlotLink();
	CreateMainWindowStyle();
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
void UiMainWindow::CreateTabWidgets()
{
	m_shift_tab = new QWidget;
	QHBoxLayout* hLayShift = new QHBoxLayout;
	m_rotateClkwise = new QPushButton(QIcon(":/icon/rotate_clockwise.ico"), "", this);
	m_rotateClkwise->setToolTip("Rotate the picture clockwise");
	connect(m_rotateClkwise, SIGNAL(clicked()), this, SLOT(RotateClkwise()));
	m_rotateCntrClkwise = new QPushButton(QIcon(":/icon/rotate_cntrclockwise.ico"), "", this);
	m_rotateCntrClkwise->setToolTip("Rotate the picture counter clockwise");
	connect(m_rotateCntrClkwise, SIGNAL(clicked()), this, SLOT(RotateCntrClkwise()));
	m_mirrorH = new QPushButton(QIcon(":/icon/mirror_horizontally.ico"), "", this);
	m_mirrorH->setToolTip("Get the horizontal mirror image of the picture");
	connect(m_mirrorH, SIGNAL(clicked()), this, SLOT(MirrorH()));
	m_mirrorV = new QPushButton(QIcon(":/icon/mirror_vertically.ico"), "", this);
	m_mirrorV->setToolTip("Get the vertically mirror image of the picture");
	connect(m_mirrorV, SIGNAL(clicked()), this, SLOT(MirrorV()));
	connect(this, SIGNAL(ImageLoaded(bool)), m_shift_tab, SLOT(setEnabled(bool)));
	hLayShift->addWidget(m_rotateClkwise);
	hLayShift->addWidget(m_rotateCntrClkwise);
	hLayShift->addWidget(m_mirrorH);
	hLayShift->addWidget(m_mirrorV);
	hLayShift->addStretch();
	m_shift_tab->setLayout(hLayShift);

	m_hist_tab = new QWidget;
	QHBoxLayout* hLayHist = new QHBoxLayout;
	m_dispHist = new QPushButton("hist", this);
	connect(m_dispHist, SIGNAL(clicked()), this, SLOT(CreateHistDialog()));
	m_histEqualize = new QPushButton("equalize", this);
	connect(m_histEqualize, SIGNAL(clicked()), this, SLOT(EqualizeHist()));
	m_histMatch = new QPushButton("match", this);
	connect(m_histMatch, SIGNAL(clicked()), this, SLOT(MatchHist()));
	m_enhance = new QPushButton("enhance", this);
	connect(m_enhance, SIGNAL(clicked()), this, SLOT(Enhance()));
	connect(this, SIGNAL(ImageLoaded(bool)), m_hist_tab, SLOT(setEnabled(bool)));
	hLayHist->addWidget(m_dispHist);
	hLayHist->addWidget(m_histEqualize);
	hLayHist->addWidget(m_histMatch);
	hLayHist->addWidget(m_enhance);
	hLayHist->addStretch();
	m_hist_tab->setLayout(hLayHist);

	m_filter_tab = new QWidget;
	m_gray = new QPushButton("gray", this);
	connect(m_gray, SIGNAL(clicked()), this, SLOT(Gray()));
	m_sobelSharpen = new QPushButton("sobel", this);
	connect(m_sobelSharpen, SIGNAL(clicked()), this, SLOT(SobelSharpen()));
	m_laplaceSharpen = new QPushButton("laplace", this);
	connect(m_laplaceSharpen, SIGNAL(clicked()), this, SLOT(LaplaceSharpen()));
	m_medianFilter = new QPushButton("medianF", this);
	connect(m_medianFilter, SIGNAL(clicked()), this, SLOT(MedianFilter()));
	m_medianBlur = new QPushButton("medianB", this);
	connect(m_medianBlur, SIGNAL(clicked()), this, SLOT(MedianBlur()));
	m_guassinBlur = new QPushButton("guassin", this);
	connect(m_guassinBlur, SIGNAL(clicked()), this, SLOT(GuassinBlur()));
	m_otsuBinary = new QPushButton("otsu", this);
	connect(m_otsuBinary, SIGNAL(clicked()), this, SLOT(OtsuBinary()));
	m_erode = new QPushButton("erode", this);
	connect(m_erode, SIGNAL(clicked()), this, SLOT(Erode()));
	m_dilate = new QPushButton("dilate", this);
	connect(m_dilate, SIGNAL(clicked()), this, SLOT(Dilate()));
	m_holeFill = new QPushButton("hole", this);
	connect(m_holeFill, SIGNAL(clicked()), this, SLOT(HoleFill()));
	m_engrave = new QPushButton("engrave", this);
	connect(m_engrave, SIGNAL(clicked()), this, SLOT(Engrave()));
	m_negative = new QPushButton("negative", this);
	connect(m_negative, SIGNAL(clicked()), this, SLOT(Negative()));
	m_comFog = new QPushButton("fog", this);
	connect(m_comFog, SIGNAL(clicked()), this, SLOT(ComFog()));
	m_sketch = new QPushButton("sketch", this);
	connect(m_sketch, SIGNAL(clicked()), this, SLOT(Sketch()));
	connect(this, SIGNAL(ImageLoaded(bool)), m_filter_tab, SLOT(setEnabled(bool)));
	QHBoxLayout* hLayFilter = new QHBoxLayout;
	hLayFilter->addWidget(m_gray);
	hLayFilter->addWidget(m_sobelSharpen);
	hLayFilter->addWidget(m_laplaceSharpen);
	hLayFilter->addWidget(m_medianFilter);
	hLayFilter->addWidget(m_medianBlur);
	hLayFilter->addWidget(m_guassinBlur);
	hLayFilter->addWidget(m_otsuBinary);
	hLayFilter->addWidget(m_holeFill);
	hLayFilter->addWidget(m_dilate);
	hLayFilter->addWidget(m_erode);
	hLayFilter->addWidget(m_engrave);
	hLayFilter->addWidget(m_negative);
	hLayFilter->addWidget(m_comFog);
	hLayFilter->addWidget(m_sketch);
	hLayFilter->addStretch();
	m_filter_tab->setLayout(hLayFilter);

	m_detect_tab = new QWidget;
	m_houghTransform = new QPushButton("hough", this);
	connect(m_houghTransform, SIGNAL(clicked()), this, SLOT(HoughTransform()));
	connect(this, SIGNAL(ImageLoaded(bool)), m_detect_tab, SLOT(setEnabled(bool)));
	QHBoxLayout* hLayDetect = new QHBoxLayout;
	hLayDetect->addWidget(m_houghTransform);
	hLayDetect->addStretch();
	m_detect_tab->setLayout(hLayDetect);

	m_integrated_tab = new QWidget;
	m_cicle_incision_detect = new QPushButton("circle incision detect", this);
	connect(m_cicle_incision_detect, SIGNAL(clicked()), this, SLOT(CircleIncisionDetection()));
	connect(this, SIGNAL(ImageLoaded(bool)), m_integrated_tab, SLOT(setEnabled(bool)));
	QHBoxLayout* hLayIntegrate = new QHBoxLayout;
	hLayIntegrate->addWidget(m_cicle_incision_detect);
	hLayIntegrate->addStretch();
	m_integrated_tab->setLayout(hLayIntegrate);

	m_tabWidget = new QTabWidget(this);
	m_tabWidget->addTab(m_shift_tab, "Shift");
	m_tabWidget->addTab(m_hist_tab, "Histogram");
	m_tabWidget->addTab(m_filter_tab, "Filtering");
	m_tabWidget->addTab(m_detect_tab, "Detecting");
	m_tabWidget->addTab(m_integrated_tab, "Integrated");

	m_tabWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}


/*---------------------------------------------------------------------
Fuction:        CreatePicDispWidgets(const QString &fileName)

Description:    1. Creat picture display area in the mainwidow center widget
				2. Init image file to display

Input:          File path of the image file to display

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::CreatePicDispWidgets(const QString &fileName)
{
	m_dispArea = new QLabel;
	m_dispArea->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	m_dispArea->setAlignment(Qt::AlignCenter);
	m_dispArea->setAcceptDrops(false);

	if (fileName != 0){
		m_PanImage = PanImageIO::GetInstance()->ReadPanImage(fileName);
		SetImage(m_PanImage);
	}
	else {
		SetHasImage(false);
	}

	m_dispFrame = new QScrollArea;
	m_dispFrame->setAutoFillBackground(true);
	m_dispFrame->setBackgroundRole(QPalette::Light);
	m_dispFrame->setWidgetResizable(true);
	m_dispFrame->setAcceptDrops(false);
	m_dispFrame->setWidget(m_dispArea);
}


/*---------------------------------------------------------------------
Fuction:        CreatCenterWidget(const QString& fileName)

Description:    1. Creat the layout of the center widget of mainwindow
				2. transfer the file path parameter

Input:          File path of the image file to display

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::CreateCenterWidget(const QString& fileName)
{
	CreateTabWidgets();
	CreatePicDispWidgets(fileName);

	m_centerSplitter = new QSplitter(Qt::Vertical);
	m_centerSplitter->addWidget(m_tabWidget);
	m_centerSplitter->addWidget(m_dispFrame);
	m_centerSplitter->setStretchFactor(1,1);

	setCentralWidget(m_centerSplitter);
	setAcceptDrops(false);
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
void UiMainWindow::CreateStatusBar()
{
	m_openPic = new QPushButton(QIcon(":/icon/open_pic.ico"), "", this);
	m_openPic->setToolTip("Open a picture");
	connect(m_openPic, SIGNAL(clicked()), this, SLOT(OpenPic()));
	m_save = new QPushButton(QIcon(":/icon/save.ico"), "", this);
	m_save->setToolTip("Save and cover current picture");
	connect(m_save, SIGNAL(clicked()), this, SLOT(Save()));
	connect(this, SIGNAL(ImageLoaded(bool)), m_save, SLOT(setEnabled(bool)));
	m_saveAs = new QPushButton(QIcon(":/icon/saveAs.ico"), "", this);
	m_saveAs->setToolTip("Save current picture as another file");
	connect(m_saveAs, SIGNAL(clicked()), this, SLOT(SaveAs()));
	connect(this, SIGNAL(ImageLoaded(bool)), m_saveAs, SLOT(setEnabled(bool)));

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
	connect(this, SIGNAL(ImageLoaded(bool)), m_curPicIndexBox, SLOT(setEnabled(bool)));

	m_prevPic = new QPushButton(QIcon(":/icon/previous_pic.ico"),"", this);
	connect(m_prevPic, SIGNAL(clicked()), this, SLOT(PrevPic()));
	connect(this, SIGNAL(ImageLoaded(bool)), m_prevPic, SLOT(setEnabled(bool)));
	m_nextPic = new QPushButton(QIcon(":/icon/next_pic.ico"),"", this);
	connect(m_nextPic, SIGNAL(clicked()), this, SLOT(NextPic()));
	connect(this, SIGNAL(ImageLoaded(bool)), m_nextPic, SLOT(setEnabled(bool)));

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
	connect(this, SIGNAL(ImageLoaded(bool)), m_zoomRateBox, SLOT(setEnabled(bool)));

	QLabel* widthSentence = new QLabel("Width:", this);
	connect(this, SIGNAL(ImageLoaded(bool)), widthSentence, SLOT(setEnabled(bool)));
	m_curPicWidth = new QLabel("", this);
	connect(this, SIGNAL(ImageLoaded(bool)), m_curPicWidth, SLOT(setEnabled(bool)));
	QLabel* heightSentence = new QLabel("Height:", this);
	connect(this, SIGNAL(ImageLoaded(bool)), heightSentence, SLOT(setEnabled(bool)));
	m_curPicHeight = new QLabel("", this);
	connect(this, SIGNAL(ImageLoaded(bool)), m_curPicHeight, SLOT(setEnabled(bool)));

	m_statusBar = statusBar();
	m_statusBar->addWidget(m_openPic);
	m_statusBar->addWidget(m_save);
	m_statusBar->addWidget(m_saveAs);
	m_statusBar->addWidget(m_prevPic);
	m_statusBar->addWidget(m_curPicIndexBox);
	m_statusBar->addWidget(m_nextPic);
	m_statusBar->addWidget(m_zoomRateBox);
	m_statusBar->addWidget(widthSentence);
	m_statusBar->addWidget(m_curPicWidth);
	m_statusBar->addWidget(heightSentence);
	m_statusBar->addWidget(m_curPicHeight);
}


/*---------------------------------------------------------------------
Fuction:        CreatGlobalSigSlotLink()

Description:    Link global signals and slots

Input:          None

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::CreateGlobalSigSlotLink()
{
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
void UiMainWindow::CreateMainWindowStyle()
{
	setAcceptDrops(true);
	setWindowTitle(tr("%1[*] - %2").arg(m_fileName).arg("panpic"));
	connect(&subThread, SIGNAL(allTransformDone()), this, SLOT(AllTransformDone()));
}


/*---------------------------------------------------------------------
Fuction:        CreateOthers()

Description:    Create all the other image processing related objects

Input:          None

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::InitGlobalVariables()
{
	m_curFileIndex = 0;
	m_curFileRange = 0;
}

void UiMainWindow::AddTransform(Transform* transform)
{
	subThread.addTransform(transform);

	m_openPic->setEnabled(false);
	m_nextPic->setEnabled(false);
	m_prevPic->setEnabled(false);
}

void UiMainWindow::AllTransformDone()
{
	SetImage(m_PanImage);

	m_openPic->setEnabled(true);
	m_nextPic->setEnabled(true);
	m_prevPic->setEnabled(true);

	setWindowModified(true);
}

/*---------------------------------------------------------------------
Fuction:        OpenPic()

Description:    Slot for "m_openPic" action

Input:          None

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::OpenPic()
{
	QString selectedFilter = tr("BMP(*.bmp)");
	m_fileName = QFileDialog::getOpenFileName(this,
											  tr("Open File"),
											  "G:/operation/",
											  tr("JPEG(*.jpg *.jpeg);; BMP(*.bmp);;"\
												 "PNG(*.png);;TIFF(*.tif)"\
												 ";;GIF(*.gif);; ICO(*.ico);; ALL(*.*)"
												),
											  &selectedFilter);
	if (m_fileName != NULL){
		m_PanImage = PanImageIO::GetInstance()->ReadPanImage(m_fileName);
		SetImage(m_PanImage);

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
}


/*---------------------------------------------------------------------
Fuction:        PrevPic()

Description:    Slot for "m_nextPic" action

Input:          None

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::PrevPic()
{
	m_curFileIndex --;
	if (m_curFileIndex >= 0){
		QString curfileName = m_curFileList.at(m_curFileIndex).absoluteFilePath();
		if (curfileName != NULL){
			m_fileName = curfileName;
			m_PanImage = PanImageIO::GetInstance()->ReadPanImage(m_fileName);
			SetImage(m_PanImage);
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
void UiMainWindow::NextPic()
{
	m_curFileIndex ++;
	if (m_curFileIndex < m_curFileRange){
		QString curfileName = m_curFileList.at(m_curFileIndex).absoluteFilePath();
		if (curfileName != NULL){
			m_fileName = curfileName;
			m_PanImage = PanImageIO::GetInstance()->ReadPanImage(m_fileName);
			SetImage(m_PanImage);
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
void UiMainWindow::Save()
{
	PanImageIO::GetInstance()->SavePanImage(m_PanImage, QFileInfo(m_fileName).absoluteFilePath());
	setWindowModified(false);
	setWindowTitle(tr("%1[*] - %2").arg(m_fileName).arg("panpic"));
	setWindowModified(false);
}


/*---------------------------------------------------------------------
Fuction:        SaveAs()

Description:    Slot for "m_saveAs" action

Input:          None

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::SaveAs()
{
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
void UiMainWindow::RotateClkwise()
{
	AddTransform(PanImageShift::GetInstance()->RotateClockWise(m_PanImage));
}


/*---------------------------------------------------------------------
Fuction:        RotateCntrClkwise()

Description:    Slot for "m_rotateCntrClkwise" action

Input:          None

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::RotateCntrClkwise()
{
	AddTransform(PanImageShift::GetInstance()->RotateCntrClockWise(m_PanImage));
}


/*---------------------------------------------------------------------
Fuction:        MirrorH()

Description:    Slot for "m_mirrorH" action

Input:          None

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::MirrorH()
{
	AddTransform(PanImageShift::GetInstance()->MirrorH(m_PanImage));
}


/*---------------------------------------------------------------------
Fuction:        MirrorV()

Description:    Slot for "m_mirrorV" action

Input:          None

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::MirrorV()
{
	AddTransform(PanImageShift::GetInstance()->MirrorV(m_PanImage));
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
void UiMainWindow::ZoomPic(int curValue)
{
	int curWidth = m_PanImage.GetMat().cols * curValue / ZOOM_SAME;
	if (m_PanImage.IsGray()){
		m_dispArea->setPixmap(QPixmap::fromImage(m_QImage.convertToFormat(QImage::Format_RGB888).scaledToWidth(curWidth)));
	}
	else
	{
		m_dispArea->setPixmap(QPixmap::fromImage(m_QImage.scaledToWidth(curWidth)));
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
void UiMainWindow::ZoomPic()
{
	QString tmpStr = QString(m_zoomRateBox->text());
	tmpStr.chop(1);
	float value = tmpStr.toFloat() / 100.0;
	int curWidth = static_cast<int>(value * float(m_PanImage.GetMat().cols));
	if (m_PanImage.IsGray())
	{
		m_dispArea->setPixmap(QPixmap::fromImage(m_QImage.convertToFormat(QImage::Format_RGB888).scaledToWidth(curWidth)));
	}
	else 
	{
		m_dispArea->setPixmap(QPixmap::fromImage(m_QImage.scaledToWidth(curWidth)));
	}
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
void UiMainWindow::ZoomRateDisp(int value)
{
	int rate = static_cast<int>(float(value) / float(ZOOM_SAME) * 100.0);
	m_zoomRateBox->setText(QString("%1%").arg(rate));
}


/*---------------------------------------------------------------------
Fuction:        ShowCurIndexPic()

Description:    SLOT -- display piture of current index in the frame

Input:          None

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::ShowCurIndexPic()
{
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
	}
}


/*---------------------------------------------------------------------
Fuction:        ShowCurPicIndex(int indexVal, int rangeVal)

Description:    SLOT -- show current picture index in current folder

Input:          indexVal -- picture index in picture file list
				rangeVal -- picture file list element num

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::ShowCurPicIndex(int indexVal, int rangeVal)
{
	m_curPicIndexBox->setText(QString("%1/%2").arg(indexVal + 1).arg(rangeVal));
	m_zoomRateBox->setText("100%");
}


void UiMainWindow::EqualizeHist()
{
	PanImageHist::GetInstance()->HistEqalization(m_PanImage);
	SetImage(m_PanImage);
}

void UiMainWindow::MatchHist()
{
	float histV[256] = {0.0};
	for (int i = 0; i < 256; i++){
		histV[i] = m_PanImage.GetMat().cols * m_PanImage.GetMat().rows / 256.0;
	}
	PanImageHist::GetInstance()->HistMatch(m_PanImage, histV);
	SetImage(m_PanImage);
}

void UiMainWindow::Enhance()
{
	PanImageHist::GetInstance()->Enhance(m_PanImage);
	SetImage(m_PanImage);
}

void UiMainWindow::CreateHistDialog()
{
	UiHistDialog* hist = new UiHistDialog(m_PanImage, m_fileName);
	hist->show();
}

void UiMainWindow::Gray()
{
	if (! m_PanImage.IsGray())
	{
		PanImageFilter::GetInstance()->Gray(m_PanImage);
		SetImage(m_PanImage);
	}
	else
	{
		QMessageBox warning(QMessageBox::Warning, "Alert!", "This is already a gray image");
		warning.exec();	
	}	
}

void UiMainWindow::SobelSharpen()
{
	if (m_PanImage.IsGray())
	{
		PanImageFilter::GetInstance()->SobelSharpen(m_PanImage);
		SetImage(m_PanImage);
	}
	else
	{
		QMessageBox warning(QMessageBox::Warning, "Alert!", "This is not a single channel image");
		warning.exec();	
	}
}

void UiMainWindow::LaplaceSharpen()
{
	PanImageFilter::GetInstance()->LaplaceSharpen(m_PanImage);
	SetImage(m_PanImage);
}

void UiMainWindow::MedianFilter()
{
	if (m_PanImage.IsGray())
	{
		PanImageFilter::GetInstance()->MedianFilter(m_PanImage);
		SetImage(m_PanImage);
	}
	else
	{
		QMessageBox warning(QMessageBox::Warning, "Alert!", "This is not a single channel image");
		warning.exec();	
	}
}

void UiMainWindow::MedianBlur()
{
	PanImageFilter::GetInstance()->MedianBlur(m_PanImage);
	SetImage(m_PanImage);
}

void UiMainWindow::GuassinBlur()
{
	PanImageFilter::GetInstance()->GuassinBlur(m_PanImage);
	SetImage(m_PanImage);
}

void UiMainWindow::OtsuBinary()
{
	if (m_PanImage.IsGray())
	{
		PanImageFilter::GetInstance()->OtsuBinary(m_PanImage);
		SetImage(m_PanImage);
	}
	else
	{
		QMessageBox warning(QMessageBox::Warning, "Alert!", "This is not a single channel image");
		warning.exec();	
	}
}

void UiMainWindow::HoleFill()
{
	if (m_PanImage.IsBinary())
	{
		PanImageFilter::GetInstance()->HoleFill(m_PanImage);
		SetImage(m_PanImage);
	}
	else
	{
		QMessageBox warning(QMessageBox::Warning, "Alert!", "This is not a binary image");
		warning.exec();	
	}
}

void UiMainWindow::HoughTransform()
{
	if (m_PanImage.IsBinary())
	{
		UiHoughTransformParam* houghParamDialog = new UiHoughTransformParam(m_PanImage,bigCircle);
		houghParamDialog->show();
	}
	else
	{
		QMessageBox warning(QMessageBox::Warning, "Alert!", "This is not a binary image");
		warning.exec();	
	}
}

void UiMainWindow::Engrave()
{
	PanImageFilter::GetInstance()->Engrave(m_PanImage);
	SetImage(m_PanImage);
}

void UiMainWindow::Negative()
{
	PanImageFilter::GetInstance()->Negative(m_PanImage);
	SetImage(m_PanImage);
}

void UiMainWindow::Erode(){
	PanImageFilter::GetInstance()->Erode(m_PanImage);
	SetImage(m_PanImage);
}

void UiMainWindow::Dilate()
{
	PanImageFilter::GetInstance()->Dilate(m_PanImage);
	SetImage(m_PanImage);
}

void UiMainWindow::ComFog()
{
	PanImageFilter::GetInstance()->ComFog(m_PanImage, 5);
	SetImage(m_PanImage);
}

void UiMainWindow::Sketch()
{
	PanImageFilter::GetInstance()->Sketch(m_PanImage);
	SetImage(m_PanImage);
}

void UiMainWindow::CircleIncisionDetection()
{
	if (m_PanImage.IsGray())
	{
		PanImageDetect::GetInstance()->CicleIncisionDetection(m_PanImage);
		SetImage(m_PanImage);
	}
	else
	{
		QMessageBox warning(QMessageBox::Warning, "Alert!", "This is not a single channel image");
		warning.exec();	
	}
}

/*---------------------------------------------------------------------
Fuction:        SetHasImage(bool value)

Description:    Set function of property -- "m_hasImage"(bool)

Input:          True or false

Output:         None
----------------------------------------------------------------------*/
void UiMainWindow::SetHasImage(bool value)
{
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
void UiMainWindow::SetImage(PanImage& newImage)
{
	m_QImage = newImage.PanImage2QImage();
	m_dispArea->setPixmap(QPixmap::fromImage(m_QImage));

	m_curPicWidth->setText(QString("%1").arg(m_QImage.width()));
	m_curPicHeight->setText(QString("%1").arg(m_QImage.height()));

	emit(ImageChanged());
	setWindowTitle(tr("%1[*] - %2").arg(m_fileName).arg("panpic"));
	update();
	updateGeometry();

	SetHasImage(true);
}

void UiMainWindow::dragEnterEvent(QDragEnterEvent *event)
{
	event->acceptProposedAction();
}

void UiMainWindow::dropEvent(QDropEvent* event)
{
	QList<QUrl> urls = event->mimeData()->urls();

	if (urls.isEmpty())
	{
		return;
	}

	m_fileName = urls.first().toLocalFile();

	if (m_fileName.isEmpty())
	{
		return;
	}

	m_PanImage = PanImageIO::GetInstance()->ReadPanImage(m_fileName);
	SetImage(m_PanImage);

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
Fuction:        Overload -- wheelEvent(QWheelEvent *event)

Description:    1. To implement of mouse wheel zooming -- to picture

Input:          1. Event that trigged

Output:         True or False
----------------------------------------------------------------------*/
void UiMainWindow::wheelEvent(QWheelEvent *event)
{
	QString tmpStr = QString(m_zoomRateBox->text());
	tmpStr.chop(1);
	float value = tmpStr.toFloat() / 100.0 * ZOOM_SAME;
	int wheeledDistance = 0;
	if (QApplication::keyboardModifiers() == Qt::ControlModifier){
		wheeledDistance = (event->angleDelta() / 20).y();
		if (wheeledDistance <= -value){
			wheeledDistance = -value;
		}
		emit(MouseOnPicWheeled(wheeledDistance + value));
	}
}

