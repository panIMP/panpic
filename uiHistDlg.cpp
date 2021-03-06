#include "uiHistDlg.h"

UiHistDialog::UiHistDialog(baseImage& image, const QString& imageName, QWidget *parent) :QWidget(parent)
{
	histLabel = new QLabel;
	histLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	histLabel->setAlignment(Qt::AlignCenter);	

	save = new QPushButton("Save");
	connect(save, SIGNAL(clicked()), this, SLOT(Save()));

	QVBoxLayout* vLay1 = new QVBoxLayout;
	vLay1->addWidget(histLabel);
	QHBoxLayout* hLay1 = new QHBoxLayout;
	hLay1->addStretch();
	hLay1->addWidget(save);
	hLay1->addStretch();
	vLay1->addLayout(hLay1);
	setLayout(vLay1);

	setWindowTitle("Histogram - " + QFileInfo(imageName).fileName());
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	setAttribute(Qt::WA_DeleteOnClose);

	subThread = baseThread::GetInstance();
	connect(subThread, SIGNAL(allTransformDone()), this, SLOT(ShowResult()));
    AddTransform(new AlgHistProc::GetHistImage(image, histimg));
}

void UiHistDialog::AddTransform(baseTransform* transform)
{
	subThread->addTransform(transform);
}

void UiHistDialog::ShowResult()
{
	disconnect(subThread, SIGNAL(allTransformDone()), this, SLOT(ShowResult()));
	histLabel->setPixmap(QPixmap::fromImage(histimg.PanImage2QImage()));
	this->show();
}

void UiHistDialog::Save(){
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
        baseImage::SavePanImage(histimg, QFileInfo(fileName).absoluteFilePath());
		setWindowModified(false);
		setWindowTitle("Histogram - " + QFileInfo(fileName).fileName());
	}
}
