#include "uimainwindow.h"


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

	PanImageDetect::Destroy();
	PanImageFilter::Destroy();
	PanImageHist::Destroy();
	PanImageIO::Destroy();
	PanImageShift::Destroy();

	delete zoomValidator;
	delete picIndexValidator;
}

void UiMainWindow::CreatePicEditorApp()
{
	//	create picture editor tabs
	m_shift_tab = new QWidget(this);
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
	QHBoxLayout* hLayShift = new QHBoxLayout(this);
	hLayShift->addWidget(m_rotateClkwise);
	hLayShift->addWidget(m_rotateCntrClkwise);
	hLayShift->addWidget(m_mirrorH);
	hLayShift->addWidget(m_mirrorV);
	hLayShift->addStretch();
	m_shift_tab->setLayout(hLayShift);

	m_hist_tab = new QWidget(this);
	m_dispHist = new QPushButton("hist", this);
	connect(m_dispHist, SIGNAL(clicked()), this, SLOT(CreateHistDialog()));
	m_histEqualize = new QPushButton("equalize", this);
	connect(m_histEqualize, SIGNAL(clicked()), this, SLOT(EqualizeHist()));
	m_histMatch = new QPushButton("match", this);
	connect(m_histMatch, SIGNAL(clicked()), this, SLOT(MatchHist()));
	m_enhance = new QPushButton("enhance", this);
	connect(m_enhance, SIGNAL(clicked()), this, SLOT(Enhance()));
	connect(this, SIGNAL(ImageLoaded(bool)), m_hist_tab, SLOT(setEnabled(bool)));
	QHBoxLayout* hLayHist = new QHBoxLayout(this);
	hLayHist->addWidget(m_dispHist);
	hLayHist->addWidget(m_histEqualize);
	hLayHist->addWidget(m_histMatch);
	hLayHist->addWidget(m_enhance);
	hLayHist->addStretch();
	m_hist_tab->setLayout(hLayHist);

	m_filter_tab = new QWidget(this);
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
	QHBoxLayout* hLayFilter = new QHBoxLayout(this);
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

	m_detect_tab = new QWidget(this);
	m_houghTransform = new QPushButton("hough", this);
	connect(m_houghTransform, SIGNAL(clicked()), this, SLOT(HoughTransform()));
	connect(this, SIGNAL(ImageLoaded(bool)), m_detect_tab, SLOT(setEnabled(bool)));
	QHBoxLayout* hLayDetect = new QHBoxLayout(this);
	hLayDetect->addWidget(m_houghTransform);
	hLayDetect->addStretch();
	m_detect_tab->setLayout(hLayDetect);

	m_integrated_tab = new QWidget(this);
	m_cicle_incision_detect = new QPushButton("circle incision detect", this);
	connect(m_cicle_incision_detect, SIGNAL(clicked()), this, SLOT(CircleIncisionDetection()));
	connect(this, SIGNAL(ImageLoaded(bool)), m_integrated_tab, SLOT(setEnabled(bool)));
	QHBoxLayout* hLayIntegrate = new QHBoxLayout(this);
	hLayIntegrate->addWidget(m_cicle_incision_detect);
	hLayIntegrate->addStretch();
	m_integrated_tab->setLayout(hLayIntegrate);

	m_picEditorTabWidget = new QTabWidget(this);
	m_picEditorTabWidget->addTab(m_shift_tab, "Shift");
	m_picEditorTabWidget->addTab(m_hist_tab, "Histogram");
	m_picEditorTabWidget->addTab(m_filter_tab, "Filtering");
	m_picEditorTabWidget->addTab(m_detect_tab, "Detecting");
	m_picEditorTabWidget->addTab(m_integrated_tab, "Integrated");

	//	create picture editor display frame
	m_dispArea = new QLabel(this);
	m_dispArea->setAlignment(Qt::AlignCenter);
	m_dispArea->setAcceptDrops(false);

	m_dispFrame = new QScrollArea(this);
	m_dispFrame->setAutoFillBackground(true);
	m_dispFrame->setBackgroundRole(QPalette::Light);
	m_dispFrame->setWidgetResizable(true);
	m_dispFrame->setAcceptDrops(false);
	m_dispFrame->setWidget(m_dispArea);

	m_picEditorSplitter = new QSplitter(Qt::Vertical, this);
	m_picEditorSplitter->addWidget(m_picEditorTabWidget);
	m_picEditorSplitter->addWidget(m_dispFrame);
	m_picEditorSplitter->setStretchFactor(1,1);
}

void UiMainWindow::CreateCenterWidget()
{
	//	create app list on the left and app frame
	m_centerWidget = new QWidget(this);
	m_appList = new QListWidget(this);
	m_appList->setFixedWidth(100);
	m_appFrame = new QStackedLayout(this);

	//	app mode 1 -- picture editor
	CreatePicEditorApp();
	m_appList->addItem("Picture Editor");
	m_appFrame->addWidget(m_picEditorSplitter);

	//	app mode 2 -- picture searcher



	//	connet app list with app frame
	connect(m_appList, SIGNAL(currentRowChanged(int)), m_appFrame, SLOT(setCurrentIndex(int)));
	m_appList->setCurrentRow(0);

	QHBoxLayout* hLay = new QHBoxLayout(this);
	hLay->addWidget(m_appList);
	hLay->addLayout(m_appFrame);
	m_centerWidget->setLayout(hLay);

	setCentralWidget(m_centerWidget);
	setAcceptDrops(false);
	setMinimumSize(m_minWidth, m_minHeight);
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}


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
	picIndexValidator = new QRegExpValidator(picIndexRegexp, m_curPicIndexBox);
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
	zoomValidator = new QRegExpValidator(zoomRegexp, m_zoomRateBox);
	m_zoomRateBox->setValidator(zoomValidator);
	// zoom rate box content edited --> zoom pic according to the new content
	connect(m_zoomRateBox, SIGNAL(returnPressed()), this, SLOT(ZoomPic()));
	connect(this, SIGNAL(ImageLoaded(bool)), m_zoomRateBox, SLOT(setEnabled(bool)));

	QLabel* widthSentence = new QLabel("Width:", this);
	connect(this, SIGNAL(ImageLoaded(bool)), widthSentence, SLOT(setEnabled(bool)));
	m_curPicWidth = new QLabel("", this);
	m_curPicWidth->setFixedWidth(50);
	connect(this, SIGNAL(ImageLoaded(bool)), m_curPicWidth, SLOT(setEnabled(bool)));
	QLabel* heightSentence = new QLabel("Height:", this);
	connect(this, SIGNAL(ImageLoaded(bool)), heightSentence, SLOT(setEnabled(bool)));
	m_curPicHeight = new QLabel("", this);
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
	setWindowTitle(tr("%1[*] - %2").arg(m_fileName).arg("panpic"));

	setAttribute(Qt::WA_DeleteOnClose);

	connect(subThread, SIGNAL(allTransformDone()), this, SLOT(AllTransformDone()));
}


void UiMainWindow::InitGlobalVariables()
{
	subThread = TransformThread::GetInstance();

	SetHasImage(false);

	m_curFileIndex = 0;
	m_curFileRange = 0;

	bigCircle.hasValue = false;
	smallCircle.hasValue = false;
}

void UiMainWindow::AddTransform(Transform* transform)
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


void UiMainWindow::Save()
{
	PanImageIO::GetInstance()->SavePanImage(m_PanImage, QFileInfo(m_fileName).absoluteFilePath());
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
		PanImageIO::GetInstance()->SavePanImage(m_PanImage, QFileInfo(fileName).absoluteFilePath());
		setWindowModified(false);
		setWindowTitle("panpic - " + QFileInfo(fileName).fileName());
	}
	setWindowModified(false);
}


void UiMainWindow::RotateClkwise()
{
	AddTransform(PanImageShift::GetInstance()->RotateClockWise(m_PanImage));
}


void UiMainWindow::RotateCntrClkwise()
{
	AddTransform(PanImageShift::GetInstance()->RotateCntrClockWise(m_PanImage));
}


void UiMainWindow::MirrorH()
{
	AddTransform(PanImageShift::GetInstance()->MirrorH(m_PanImage));
}


void UiMainWindow::MirrorV()
{
	AddTransform(PanImageShift::GetInstance()->MirrorV(m_PanImage));
}


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
		SetImage(PanImageIO::GetInstance()->ReadPanImage(m_fileName));
	}
}


void UiMainWindow::ShowCurPicIndex(int indexVal, int rangeVal)
{
	m_curPicIndexBox->setText(QString("%1/%2").arg(indexVal + 1).arg(rangeVal));
	m_zoomRateBox->setText("100%");
}


void UiMainWindow::EqualizeHist()
{
	AddTransform(PanImageHist::GetInstance()->HistEqalization(m_PanImage));
}

void UiMainWindow::MatchHist()
{
	float histV[256] = {0.0};
	for (int i = 0; i < 256; i++){
		histV[i] = m_PanImage.GetMat().cols * m_PanImage.GetMat().rows / 256.0;
	}
	AddTransform(PanImageHist::GetInstance()->HistMatch(m_PanImage, histV));
}

void UiMainWindow::Enhance()
{
	AddTransform(PanImageHist::GetInstance()->Enhance(m_PanImage));
}

void UiMainWindow::CreateHistDialog()
{
	hist = new UiHistDialog(m_PanImage, m_fileName);
}

void UiMainWindow::Gray()
{
	if (! m_PanImage.IsGray())
	{
		AddTransform(PanImageFilter::GetInstance()->Gray(m_PanImage));
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
		AddTransform(PanImageFilter::GetInstance()->SobelSharpen(m_PanImage));
	}
	else
	{
		QMessageBox warning(QMessageBox::Warning, "Alert!", "This is not a single channel image");
		warning.exec();	
	}
}

void UiMainWindow::LaplaceSharpen()
{
	AddTransform(PanImageFilter::GetInstance()->LaplaceSharpen(m_PanImage));
}

void UiMainWindow::MedianFilter()
{
	if (m_PanImage.IsGray())
	{
		AddTransform(PanImageFilter::GetInstance()->MedianFilter(m_PanImage));
	}
	else
	{
		QMessageBox warning(QMessageBox::Warning, "Alert!", "This is not a single channel image");
		warning.exec();	
	}
}

void UiMainWindow::MedianBlur()
{
	AddTransform(PanImageFilter::GetInstance()->MedianBlur(m_PanImage));
}

void UiMainWindow::GuassinBlur()
{
	AddTransform(PanImageFilter::GetInstance()->GuassinBlur(m_PanImage));
}

void UiMainWindow::OtsuBinary()
{
	if (m_PanImage.IsGray())
	{
		AddTransform(PanImageFilter::GetInstance()->OtsuBinary(m_PanImage));
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
		AddTransform(PanImageFilter::GetInstance()->HoleFill(m_PanImage));
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
		houghParamDialog = new UiHoughTransformParam(bigCircle, m_PanImage);
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
	AddTransform(PanImageFilter::GetInstance()->Engrave(m_PanImage));
}

void UiMainWindow::Negative()
{
	AddTransform(PanImageFilter::GetInstance()->Negative(m_PanImage));
}

void UiMainWindow::Erode(){
	AddTransform(PanImageFilter::GetInstance()->Erode(m_PanImage));
}

void UiMainWindow::Dilate()
{
	AddTransform(PanImageFilter::GetInstance()->Dilate(m_PanImage));
}

void UiMainWindow::ComFog()
{
	AddTransform(PanImageFilter::GetInstance()->ComFog(m_PanImage, 5));
}

void UiMainWindow::Sketch()
{
	AddTransform(PanImageFilter::GetInstance()->Sketch(m_PanImage));
}

void UiMainWindow::CircleIncisionDetection()
{
	if (m_PanImage.IsGray())
	{
		AddTransform(PanImageDetect::GetInstance(m_PanImage)->CicleIncisionDetection(m_PanImage,
															GlobalParams::BIG_CIRCLE_MIN,
															GlobalParams::BIG_CIRCLE_MAX,
															GlobalParams::SEARCH_STEP,
															0,
															m_PanImage.width(),
															0,
															m_PanImage.height(),
															100,
															bigCircle,
															smallCircle));
	}
	else
	{
		QMessageBox warning(QMessageBox::Warning, "Alert!", "This is not a single channel image");
		warning.exec();	
	}
}


void UiMainWindow::SetHasImage(bool value)
{
	m_hasImage = value;
	emit(ImageLoaded(value));
}


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

