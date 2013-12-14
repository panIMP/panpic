#include "uiMainWin.h"


UiMainWindow::UiMainWindow(QWidget *parent) : QMainWindow(parent)
{
	InitGlobalVariables();
	CreateCenterWidget();
	CreateStatusBar();
	CreateGlobalSigSlotLink();
	CreateMainWindowStyle();
}

UiMainWindow::~UiMainWindow()
{
	subThread->destroyed();
}

void UiMainWindow::CreatePicEditorApp()
{
	//	create picture editor tabs
	m_shift_tab = new QWidget;
	m_rotateClkwise = new QPushButton(QIcon(":/icon/rotate_clockwise.ico"), "");
	m_rotateClkwise->setToolTip("Rotate the picture clockwise");
	connect(m_rotateClkwise, SIGNAL(clicked()), this, SLOT(RotateClkwise()));
	m_rotateCntrClkwise = new QPushButton(QIcon(":/icon/rotate_cntrclockwise.ico"), "");
	m_rotateCntrClkwise->setToolTip("Rotate the picture counter clockwise");
	connect(m_rotateCntrClkwise, SIGNAL(clicked()), this, SLOT(RotateCntrClkwise()));
	m_mirrorH = new QPushButton(QIcon(":/icon/mirror_horizontally.ico"), "");
	m_mirrorH->setToolTip("Get the horizontal mirror image of the picture");
	connect(m_mirrorH, SIGNAL(clicked()), this, SLOT(MirrorH()));
	m_mirrorV = new QPushButton(QIcon(":/icon/mirror_vertically.ico"), "");
	m_mirrorV->setToolTip("Get the vertically mirror image of the picture");
	connect(m_mirrorV, SIGNAL(clicked()), this, SLOT(MirrorV()));
	connect(this, SIGNAL(ImageLoaded(bool)), m_shift_tab, SLOT(setEnabled(bool)));
	QHBoxLayout* hLayShift = new QHBoxLayout();
	hLayShift->addWidget(m_rotateClkwise);
	hLayShift->addWidget(m_rotateCntrClkwise);
	hLayShift->addWidget(m_mirrorH);
	hLayShift->addWidget(m_mirrorV);
	hLayShift->addStretch();
	m_shift_tab->setLayout(hLayShift);

	m_hist_tab = new QWidget;
	m_dispHist = new QPushButton("hist");
	connect(m_dispHist, SIGNAL(clicked()), this, SLOT(CreateHistDialog()));
	m_histEqualize = new QPushButton("equalize");
	connect(m_histEqualize, SIGNAL(clicked()), this, SLOT(EqualizeHist()));
	m_histMatch = new QPushButton("match", this);
	connect(m_histMatch, SIGNAL(clicked()), this, SLOT(MatchHist()));
	m_enhance = new QPushButton("enhance", this);
	connect(m_enhance, SIGNAL(clicked()), this, SLOT(Enhance()));
	connect(this, SIGNAL(ImageLoaded(bool)), m_hist_tab, SLOT(setEnabled(bool)));
	QHBoxLayout* hLayHist = new QHBoxLayout();
	hLayHist->addWidget(m_dispHist);
	hLayHist->addWidget(m_histEqualize);
	hLayHist->addWidget(m_histMatch);
	hLayHist->addWidget(m_enhance);
	hLayHist->addStretch();
	m_hist_tab->setLayout(hLayHist);

	m_filter_tab = new QWidget;
	m_gray = new QPushButton("gray");
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
	QHBoxLayout* hLayFilter0 = new QHBoxLayout();
	hLayFilter0->addWidget(m_gray);
	hLayFilter0->addWidget(m_sobelSharpen);
	hLayFilter0->addWidget(m_laplaceSharpen);
	hLayFilter0->addWidget(m_medianFilter);
	hLayFilter0->addWidget(m_medianBlur);
	hLayFilter0->addWidget(m_guassinBlur);
	hLayFilter0->addWidget(m_otsuBinary);
	QHBoxLayout* hLayFilter1 = new QHBoxLayout();
	hLayFilter1->addWidget(m_holeFill);
	hLayFilter1->addWidget(m_dilate);
	hLayFilter1->addWidget(m_erode);
	hLayFilter1->addWidget(m_engrave);
	hLayFilter1->addWidget(m_negative);
	hLayFilter1->addWidget(m_comFog);
	hLayFilter1->addWidget(m_sketch);
	hLayFilter1->addStretch();
	QVBoxLayout* vLayFilter = new QVBoxLayout();
	vLayFilter->addLayout(hLayFilter0);
	vLayFilter->addLayout(hLayFilter1);
	m_filter_tab->setLayout(vLayFilter);

	m_detect_tab = new QWidget;
	m_houghTransform = new QPushButton("hough");
	connect(m_houghTransform, SIGNAL(clicked()), this, SLOT(HoughTransform()));
	connect(this, SIGNAL(ImageLoaded(bool)), m_detect_tab, SLOT(setEnabled(bool)));
	QHBoxLayout* hLayDetect = new QHBoxLayout();
	hLayDetect->addWidget(m_houghTransform);
	hLayDetect->addStretch();
	m_detect_tab->setLayout(hLayDetect);

	m_integrated_tab = new QWidget;
	m_cicle_incision_detect = new QPushButton("circle incision detect");
	connect(m_cicle_incision_detect, SIGNAL(clicked()), this, SLOT(CircleIncisionDetection()));
	connect(this, SIGNAL(ImageLoaded(bool)), m_integrated_tab, SLOT(setEnabled(bool)));
	QHBoxLayout* hLayIntegrate = new QHBoxLayout();
	hLayIntegrate->addWidget(m_cicle_incision_detect);
	hLayIntegrate->addStretch();
	m_integrated_tab->setLayout(hLayIntegrate);

	m_picEditorTabWidget = new QTabWidget;
	m_picEditorTabWidget->addTab(m_shift_tab, "Shift");
	m_picEditorTabWidget->addTab(m_hist_tab, "Histogram");
	m_picEditorTabWidget->addTab(m_filter_tab, "Filtering");
	m_picEditorTabWidget->addTab(m_detect_tab, "Detecting");
	m_picEditorTabWidget->addTab(m_integrated_tab, "Integrated");

	//	create picture editor display frame
	m_editArea = new QLabel;
	m_editArea->setAlignment(Qt::AlignCenter);
	m_editArea->setAcceptDrops(false);

	m_editFrame = new QScrollArea;
	m_editFrame->setAutoFillBackground(true);
	m_editFrame->setBackgroundRole(QPalette::Light);
	m_editFrame->setWidgetResizable(true);
	m_editFrame->setAcceptDrops(false);
	m_editFrame->setWidget(m_editArea);

	m_picEditorSplitter = new QSplitter(Qt::Vertical);
	m_picEditorSplitter->addWidget(m_picEditorTabWidget);
	m_picEditorSplitter->addWidget(m_editFrame);
	m_picEditorSplitter->setStretchFactor(1,1);
}


void UiMainWindow::CreatePicSearcherApp()
{
	m_setSearchFolder = new QPushButton("Search Folder");
	connect(m_setSearchFolder, SIGNAL(clicked()), this, SLOT(SelectSearchFolder()));
	m_setSearchMethod = new QComboBox;
	m_setSearchMethod->addItem("Color feature");
	m_setSearchMethod->addItem("Grain feature");
	m_setSearchMethod->addItem("Shape feature");
	m_startSearch = new QPushButton("Start");
	connect(m_startSearch, SIGNAL(clicked()), this, SLOT(StartSearch()));

	QHBoxLayout* hLay0 = new QHBoxLayout();
	hLay0->addStretch();
	hLay0->addWidget(m_setSearchFolder);
	hLay0->addWidget(m_setSearchMethod);
	hLay0->addWidget(m_startSearch);
	hLay0->addStretch();
	m_chooseLine = new QWidget;
	m_chooseLine->setLayout(hLay0);

	m_searchArea = new QLabel;
	m_searchArea->setAlignment(Qt::AlignCenter);
	m_searchArea->setAcceptDrops(false);
	m_searchArea->setFrameStyle(QFrame::Box);
	m_searchArea->setMinimumSize(300,200);

	m_traverseArea = new QLabel;
	m_traverseArea->setAlignment(Qt::AlignCenter);
	m_traverseArea->setAcceptDrops(false);
	m_traverseArea->setFrameStyle(QFrame::Box);
	m_traverseArea->setMinimumSize(300,200);

	QHBoxLayout* hLay1 = new QHBoxLayout();
	hLay1->addWidget(m_searchArea);
	hLay1->addWidget(m_traverseArea);
	m_searchLine = new QWidget;
	m_searchLine->setLayout(hLay1);

	m_resultArea1 = new QLabel;
	m_resultArea1->setFrameStyle(QFrame::Box);
	m_resultArea2 = new QLabel;
	m_resultArea2->setFrameStyle(QFrame::Box);
	m_resultArea3 = new QLabel;
	m_resultArea3->setFrameStyle(QFrame::Box);
	m_resultArea4 = new QLabel;
	m_resultArea4->setFrameStyle(QFrame::Box);
	m_resultArea5 = new QLabel;
	m_resultArea5->setFrameStyle(QFrame::Box);
	m_resultArea6 = new QLabel;
	m_resultArea6->setFrameStyle(QFrame::Box);
	m_resultArea7 = new QLabel;
	m_resultArea7->setFrameStyle(QFrame::Box);
	m_resultArea8 = new QLabel;
	m_resultArea8->setFrameStyle(QFrame::Box);

	m_resultArea1->setMinimumSize(150, 100);
	m_resultArea2->setMinimumSize(150, 100);
	m_resultArea3->setMinimumSize(150, 100);
	m_resultArea4->setMinimumSize(150, 100);
	m_resultArea5->setMinimumSize(150, 100);
	m_resultArea6->setMinimumSize(150, 100);
	m_resultArea7->setMinimumSize(150, 100);
	m_resultArea8->setMinimumSize(150, 100);

	QHBoxLayout* hLay2 = new QHBoxLayout();
	hLay2->addWidget(m_resultArea1);
	hLay2->addWidget(m_resultArea2);
	hLay2->addWidget(m_resultArea3);
	hLay2->addWidget(m_resultArea4);
	m_resultLine1 = new QWidget;
	m_resultLine1->setLayout(hLay2);

	QHBoxLayout* hLay3 = new QHBoxLayout();
	hLay3->addWidget(m_resultArea5);
	hLay3->addWidget(m_resultArea6);
	hLay3->addWidget(m_resultArea7);
	hLay3->addWidget(m_resultArea8);
	m_resultLine2 = new QWidget;
	m_resultLine2->setLayout(hLay3);

	m_picSearchSplitter = new QSplitter(Qt::Vertical);
	m_picSearchSplitter->addWidget(m_chooseLine);
	m_picSearchSplitter->addWidget(m_searchLine);
	m_picSearchSplitter->addWidget(m_resultLine1);
	m_picSearchSplitter->addWidget(m_resultLine2);
	m_picSearchSplitter->setStretchFactor(1,1);
}


void UiMainWindow::CreateCenterWidget()
{
	//	create app list on the left and app frame
	m_centerWidget = new QWidget;
	m_appList = new QListWidget;
	m_appList->setFixedWidth(100);
	m_appFrame = new QStackedLayout;

	//	app mode 1 -- picture editor
	CreatePicEditorApp();
	m_appList->addItem("Picture Editor");
	m_appFrame->addWidget(m_picEditorSplitter);

	//	app mode 2 -- picture searcher
	CreatePicSearcherApp();
	m_appList->addItem("Picture Search");
	m_appFrame->addWidget(m_picSearchSplitter);

	//	connet app list with app frame
	connect(m_appList, SIGNAL(currentRowChanged(int)), m_appFrame, SLOT(setCurrentIndex(int)));
	connect(m_appList, SIGNAL(currentRowChanged(int)), this, SLOT(SetImage(int)));
	m_appList->setCurrentRow(0);

	QHBoxLayout* hLay = new QHBoxLayout();
	hLay->addWidget(m_appList);
	hLay->addLayout(m_appFrame);
	m_centerWidget->setLayout(hLay);

	setCentralWidget(m_centerWidget);
}


void UiMainWindow::CreateStatusBar()
{
	m_openPic = new QPushButton(QIcon(":/icon/open_pic.ico"), "");
	m_openPic->setToolTip("Open a picture");
	connect(m_openPic, SIGNAL(clicked()), this, SLOT(OpenPic()));
	m_save = new QPushButton(QIcon(":/icon/save.ico"), "");
	m_save->setToolTip("Save and cover current picture");
	connect(m_save, SIGNAL(clicked()), this, SLOT(Save()));
	connect(this, SIGNAL(ImageLoaded(bool)), m_save, SLOT(setEnabled(bool)));
	m_saveAs = new QPushButton(QIcon(":/icon/saveAs.ico"), "");
	m_saveAs->setToolTip("Save current picture as another file");
	connect(m_saveAs, SIGNAL(clicked()), this, SLOT(SaveAs()));
	connect(this, SIGNAL(ImageLoaded(bool)), m_saveAs, SLOT(setEnabled(bool)));

	m_curPicIndexBox = new QLineEdit;
	m_curPicIndexBox->setText("0/0");
	m_curPicIndexBox->setMaximumWidth(50);
	m_curPicIndexBox->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	// use regular expression to restrict the input to be like 'dd/dd'
	// \d should be set as \\
	// The C++ compiler transforms backslashes in strings. To include a \ in a regexp,
	// enter it twice, i.e. \\.
	// To match the backslash character itself, enter it four times, i.e. \\\\.
	QRegExp picIndexRegexp("^\\d*/\\d*$");
	picIndexValidator = new QRegExpValidator(picIndexRegexp, m_curPicIndexBox);
	m_curPicIndexBox->setValidator(picIndexValidator);
	// pic index box content edited --> switch cur displaying picture
	connect(m_curPicIndexBox, SIGNAL(returnPressed()), this, SLOT(ShowCurIndexPic()));
	connect(this, SIGNAL(ImageLoaded(bool)), m_curPicIndexBox, SLOT(setEnabled(bool)));

	m_prevPic = new QPushButton(QIcon(":/icon/previous_pic.ico"),"");
	connect(m_prevPic, SIGNAL(clicked()), this, SLOT(PrevPic()));
	connect(this, SIGNAL(ImageLoaded(bool)), m_prevPic, SLOT(setEnabled(bool)));
	m_nextPic = new QPushButton(QIcon(":/icon/next_pic.ico"),"", this);
	connect(m_nextPic, SIGNAL(clicked()), this, SLOT(NextPic()));
	connect(this, SIGNAL(ImageLoaded(bool)), m_nextPic, SLOT(setEnabled(bool)));

	m_zoomRateBox = new QLineEdit;
	m_zoomRateBox->setText("100%");
	m_zoomRateBox->setMaximumWidth(40);
	m_zoomRateBox->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	// use regular expression to restrict the input to be like 'dd%'
	QRegExp zoomRegexp("[0-9]+%$");
	zoomValidator = new QRegExpValidator(zoomRegexp, m_zoomRateBox);
	m_zoomRateBox->setValidator(zoomValidator);
	// zoom rate box content edited --> zoom pic according to the new content
	connect(m_zoomRateBox, SIGNAL(returnPressed()), this, SLOT(ZoomPic()));
	connect(this, SIGNAL(ImageLoaded(bool)), m_zoomRateBox, SLOT(setEnabled(bool)));

	QLabel* widthSentence = new QLabel("Width:");
	connect(this, SIGNAL(ImageLoaded(bool)), widthSentence, SLOT(setEnabled(bool)));
	m_curPicWidth = new QLabel("");
	m_curPicWidth->setFixedWidth(50);
	connect(this, SIGNAL(ImageLoaded(bool)), m_curPicWidth, SLOT(setEnabled(bool)));
	QLabel* heightSentence = new QLabel("Height:");
	connect(this, SIGNAL(ImageLoaded(bool)), heightSentence, SLOT(setEnabled(bool)));
	m_curPicHeight = new QLabel("");
	m_curPicHeight->setFixedWidth(50);
	connect(this, SIGNAL(ImageLoaded(bool)), m_curPicHeight, SLOT(setEnabled(bool)));

	m_statusBar = statusBar();
	m_statusBar->addWidget(m_openPic);
	m_statusBar->addWidget(m_save);
	m_statusBar->addWidget(m_saveAs);
	m_statusBar->addWidget(m_prevPic);
	m_statusBar->addWidget(m_curPicIndexBox);
	m_statusBar->addWidget(m_nextPic);
	m_statusBar->addWidget(m_zoomRateBox);
	m_statusBar->addPermanentWidget(widthSentence);
	m_statusBar->addPermanentWidget(m_curPicWidth);
	m_statusBar->addPermanentWidget(heightSentence);
	m_statusBar->addPermanentWidget(m_curPicHeight);
}


void UiMainWindow::CreateGlobalSigSlotLink()
{
	// mouse wheeled -- > zoom pic & change zoom rate box
	connect(this, SIGNAL(MouseOnPicWheeled(int)), this, SLOT(ZoomPic(int)));
	connect(this, SIGNAL(MouseOnPicWheeled(int)), this, SLOT(ZoomRateDisp(int)));

	// "next" action or "previous" action pushed --> change pic index box content;
	connect(this, SIGNAL(PicIndexSwitched(int,int)), this, SLOT(ShowCurPicIndex(int,int)));
}


void UiMainWindow::CreateMainWindowStyle()
{
	SetHasImage(false);
	setAcceptDrops(true);
	
	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

	setWindowTitle(tr("%1[*] - %2").arg(m_fileName).arg("panpic"));

	setAttribute(Qt::WA_DeleteOnClose);

	connect(subThread, SIGNAL(allTransformDone()), this, SLOT(AllTransformDone()));
}


void UiMainWindow::InitGlobalVariables()
{
	subThread = baseThread::GetInstance();

	SetHasImage(false);

	m_curFileIndex = 0;
	m_curFileRange = 0;

	bigCircle.hasValue = false;
	smallCircle.hasValue = false;
	hParam.isInited = false;
}

void UiMainWindow::AddTransform(baseTransform* transform)
{
	subThread->addTransform(transform);

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

void UiMainWindow::SetImage(int curRow)
{
	if (m_QImage.isNull())
	{
		return;
	}

	switch (curRow)
	{
	case 0:
		m_editArea->setPixmap(QPixmap::fromImage(m_QImage));
		break;
	case 1:
		if (m_PanImage.IsGray()){
			m_searchArea->setPixmap(QPixmap::fromImage(
			m_QImage.convertToFormat(QImage::Format_RGB888).
			scaled(m_searchArea->size(), Qt::KeepAspectRatio)));
		}
		else
		{
			m_searchArea->setPixmap(QPixmap::fromImage(
			m_QImage.scaled(m_searchArea->size(), Qt::KeepAspectRatio)));
		}
		break;
	default:
		break;
	}

	update();
	updateGeometry();
}

void UiMainWindow::OpenPic()
{
	QString selectedFilter = tr("ALL(*.*)");
	m_fileName = QFileDialog::getOpenFileName(this,
											  tr("Open File"),
											  "E:/baiduCloud/pics",
											  tr("JPEG(*.jpg *.jpeg);; BMP(*.bmp);;"\
												 "PNG(*.png);;TIFF(*.tif)"\
												 ";;GIF(*.gif);; ICO(*.ico);; ALL(*.*)"
												),
											  &selectedFilter);
	if (m_fileName != NULL){
		m_PanImage = baseImage::ReadPanImage(m_fileName);
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


void UiMainWindow::PrevPic()
{
	m_curFileIndex --;
	if (m_curFileIndex >= 0){
		QString curfileName = m_curFileList.at(m_curFileIndex).absoluteFilePath();
		if (curfileName != NULL){
			m_fileName = curfileName;
			m_PanImage = baseImage::ReadPanImage(m_fileName);
			SetImage(m_PanImage);
		}
	}
	else {
		m_curFileIndex ++;
	}

	// emit the signal that fileindex and filerange has changed
	emit(PicIndexSwitched(m_curFileIndex, m_curFileRange));
}


void UiMainWindow::NextPic()
{
	m_curFileIndex ++;
	if (m_curFileIndex < m_curFileRange){
		QString curfileName = m_curFileList.at(m_curFileIndex).absoluteFilePath();
		if (curfileName != NULL){
			m_fileName = curfileName;
			m_PanImage = baseImage::ReadPanImage(m_fileName);
			SetImage(m_PanImage);
		}
	}
	else {
		m_curFileIndex --;
	}

	// emit the signal that fileindex and filerange has changed
	emit(PicIndexSwitched(m_curFileIndex, m_curFileRange));
}


void UiMainWindow::Save()
{
	baseImage::SavePanImage(m_PanImage, QFileInfo(m_fileName).absoluteFilePath());
	setWindowModified(false);
	setWindowTitle(tr("%1[*] - %2").arg(m_fileName).arg("panpic"));
	setWindowModified(false);
}


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
		baseImage::SavePanImage(m_PanImage, QFileInfo(fileName).absoluteFilePath());
		setWindowModified(false);
		setWindowTitle("panpic - " + QFileInfo(fileName).fileName());
	}
	setWindowModified(false);
}


void UiMainWindow::RotateClkwise()
{
	AddTransform(new AlgShift::RotateTransform(AlgShift::ROTATE_CLOCKWISE, m_PanImage));
}


void UiMainWindow::RotateCntrClkwise()
{
	AddTransform(new AlgShift::RotateTransform(AlgShift::ROTATE_COUNTERCLOCKWISE, m_PanImage));
}


void UiMainWindow::MirrorH()
{
	AddTransform(new AlgShift::FlipTransform(AlgShift::MIRROR_HORIZONGTALLY, m_PanImage));
}


void UiMainWindow::MirrorV()
{
	AddTransform(new AlgShift::FlipTransform(AlgShift::MIRROR_VERTICALLY, m_PanImage));
}


void UiMainWindow::ZoomPic(int curValue)
{
	int curWidth = m_PanImage.GetMat().cols * curValue / ZOOM_SAME;
	if (m_PanImage.IsGray()){
		m_editArea->setPixmap(QPixmap::fromImage
				 (m_QImage.convertToFormat(QImage::Format_RGB888).scaledToWidth(curWidth)));
	}
	else
	{
		m_editArea->setPixmap(QPixmap::fromImage(m_QImage.scaledToWidth(curWidth)));
	}
	update();
	updateGeometry();
}


void UiMainWindow::ZoomPic()
{
	QString tmpStr = QString(m_zoomRateBox->text());
	tmpStr.chop(1);
	float value = tmpStr.toFloat() / 100.0;
	int curWidth = static_cast<int>(value * float(m_PanImage.GetMat().cols));
	if (m_PanImage.IsGray())
	{
		m_editArea->setPixmap(QPixmap::fromImage(m_QImage.convertToFormat(QImage::Format_RGB888).scaledToWidth(curWidth)));
	}
	else 
	{
		m_editArea->setPixmap(QPixmap::fromImage(m_QImage.scaledToWidth(curWidth)));
	}
	update();
	updateGeometry();
}


void UiMainWindow::ZoomRateDisp(int value)
{
	int rate = static_cast<int>(float(value) / float(ZOOM_SAME) * 100.0);
	m_zoomRateBox->setText(QString("%1%").arg(rate));
}


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
		SetImage(baseImage::ReadPanImage(m_fileName));
	}
}


void UiMainWindow::ShowCurPicIndex(int indexVal, int rangeVal)
{
	m_curPicIndexBox->setText(QString("%1/%2").arg(indexVal + 1).arg(rangeVal));
	m_zoomRateBox->setText("100%");
}


void UiMainWindow::EqualizeHist()
{
	AddTransform(new AlgHistProc::HistEqualize(m_PanImage));
}

void UiMainWindow::MatchHist()
{
	float histV[256] = {0.0};
	for (int i = 0; i < 256; i++){
		histV[i] = m_PanImage.GetMat().cols * m_PanImage.GetMat().rows / 256.0;
	}
	AddTransform(new AlgHistProc::HistMatch(m_PanImage, histV));
}

void UiMainWindow::Enhance()
{
	AddTransform(new AlgHistProc::Enhance(m_PanImage));
}

void UiMainWindow::CreateHistDialog()
{
	hist = new UiHistDialog(m_PanImage, m_fileName);
}

void UiMainWindow::Gray()
{
	if (! m_PanImage.IsGray())
	{
		AddTransform(new AlgFilter::Gray(m_PanImage));
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
		AddTransform(new AlgFilter::SobelSharpen(m_PanImage));
	}
	else
	{
		QMessageBox warning(QMessageBox::Warning, "Alert!", "This is not a single channel image");
		warning.exec();	
	}
}

void UiMainWindow::LaplaceSharpen()
{
	AddTransform(new AlgFilter::LaplaceSharpen(m_PanImage));
}

void UiMainWindow::MedianFilter()
{
	if (m_PanImage.IsGray())
	{
		AddTransform(new AlgFilter::MedianBlur2(m_PanImage));
	}
	else
	{
		QMessageBox warning(QMessageBox::Warning, "Alert!", "This is not a single channel image");
		warning.exec();	
	}
}

void UiMainWindow::MedianBlur()
{
	AddTransform(new AlgFilter::MedianBlur(m_PanImage));
}

void UiMainWindow::GuassinBlur()
{
	AddTransform(new AlgFilter::GuassinBlur(m_PanImage));
}

void UiMainWindow::OtsuBinary()
{
	if (m_PanImage.IsGray())
	{
		AddTransform(new AlgFilter::Otsu(m_PanImage));
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
		AddTransform(new AlgFilter::HoleFill(m_PanImage));
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
		if (!hParam.isInited)
		{
			hParam.InitGlobalVaribles(m_PanImage);
		}
		houghParamDialog = new UiHoughDlg(bigCircle, m_PanImage, hParam);
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
	AddTransform(new AlgFilter::Engrave(m_PanImage));
}

void UiMainWindow::Negative()
{
	AddTransform(new AlgFilter::Negative(m_PanImage));
}

void UiMainWindow::Erode(){
	AddTransform(new AlgFilter::Erode(m_PanImage));
}

void UiMainWindow::Dilate()
{
	AddTransform(new AlgFilter::Dilate(m_PanImage));
}

void UiMainWindow::ComFog()
{
	AddTransform(new AlgFilter::ComFog(m_PanImage, 5));
}

void UiMainWindow::Sketch()
{
	AddTransform(new AlgFilter::Sketch(m_PanImage));
}

void UiMainWindow::CircleIncisionDetection()
{
	if (m_PanImage.IsGray())
	{
		if (!hParam.isInited)
		{
			hParam.InitGlobalVaribles(m_PanImage);
		}
		AddTransform(new AlgDetect::CicleIncisionDetection(m_PanImage,
															hParam.BIG_CIRCLE_MIN,
															hParam.BIG_CIRCLE_MAX,
															hParam.SEARCH_STEP,
															0,
															m_PanImage.width(),
															0,
															m_PanImage.height(),
															100,
															bigCircle,
															smallCircle,
															hParam));
	}
	else
	{
		QMessageBox warning(QMessageBox::Warning, "Alert!", "This is not a single channel image");
		warning.exec();	
	}
}

void UiMainWindow::SelectSearchFolder()
{
	m_searchFolder = QFileDialog::getExistingDirectory(this, "Select the search folder", "E:/baiduCloud/pics");
	if ( !m_searchFolder.isNull())
	{
		QDir dir;
		dir.setPath(m_searchFolder);
		QStringList filter;
		filter<<"*.jpg"<<"*.jpeg"<<"*.bmp"<<"*.png"<<"*gif" <<"*.ico"<<"*.tif";
		dir.setNameFilters(filter);
		m_searchFileList = dir.entryInfoList();
		unsigned int k;
		k = m_searchFileList.size();
	}
}

void UiMainWindow::StartSearch()
{

}

void UiMainWindow::SetHasImage(bool value)
{
	m_hasImage = value;
	emit(ImageLoaded(value));
}


void UiMainWindow::SetImage(baseImage& newImage)
{
	m_QImage = newImage.PanImage2QImage();

	switch (m_appList->currentRow())
	{
	case 0:
		m_editArea->setPixmap(QPixmap::fromImage(m_QImage));
		break;
	case 1:
		if (m_PanImage.IsGray()){
			m_searchArea->setPixmap(QPixmap::fromImage(
			m_QImage.convertToFormat(QImage::Format_RGB888).
			scaled(m_searchArea->size(), Qt::KeepAspectRatio)));
		}
		else
		{
			m_searchArea->setPixmap(QPixmap::fromImage(
			m_QImage.scaled(m_searchArea->size(), Qt::KeepAspectRatio)));
		}
		break;
	default:
		break;
	}

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

	m_PanImage = baseImage::ReadPanImage(m_fileName);
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

void UiMainWindow::resizeEvent(QResizeEvent *event)
{
	event->accept();

	switch (m_appList->currentRow())
	{
	case 0:
		break;
	case 1:
		if (m_PanImage.IsGray()){
			m_searchArea->setPixmap(QPixmap::fromImage(
			m_QImage.convertToFormat(QImage::Format_RGB888).
			scaled(m_searchArea->size(), Qt::KeepAspectRatio)));
		}
		else
		{
			m_searchArea->setPixmap(QPixmap::fromImage(
			m_QImage.scaled(m_searchArea->size(), Qt::KeepAspectRatio)));
		}
		break;
	default:
		break;
	}
}
