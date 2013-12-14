#include "uiHoughDlg.h"


UiHoughTransformParam::UiHoughTransformParam(AlgDetect::_Pan_Circle& circle, baseImage& image, QWidget* parent) : cle(circle) , img(image), QWidget(parent)
{
	this->subThread = baseThread::GetInstance();
	connect(subThread, SIGNAL(allTransformDone()), this, SLOT(ShowResult()));

	QLabel* iRangeText = new QLabel("x range is");
	QLabel* iText = new QLabel("x", this);
	QLabel* jRangeText = new QLabel("y range is");
	QLabel* jText = new QLabel("y", this);
	QLabel* rRangeText = new QLabel("r range is");
	QLabel* rText = new QLabel("r", this);
	QLabel* compareMark0 = new QLabel(" =< ");
	QLabel* compareMark1 = new QLabel(" < ");
	QLabel* compareMark2 = new QLabel(" =< ");
	QLabel* compareMark3 = new QLabel(" < ");
	QLabel* compareMark4 = new QLabel(" =< ");
	QLabel* compareMark5 = new QLabel(" < ");
	QLabel* searchStepText = new QLabel("search step is");

	iMin = new QLineEdit();
	iMin->setAlignment(Qt::AlignCenter);
	iMin->setText("0");
	QRegExp iMinRegExp("[0-9]+$");
	iMinValidator = new QRegExpValidator(iMinRegExp, iMin);
	iMin->setValidator(iMinValidator);
	
	iMax = new QLineEdit();
	iMax->setAlignment(Qt::AlignCenter);
	iMax->setText(QString("%1").arg(image.width()));
	QRegExp iMaxRegExp("[1-9]+$");
	iMaxValidator = new QRegExpValidator(iMaxRegExp, iMax);
	iMax->setValidator(iMaxValidator);
	
	jMin = new QLineEdit();
	jMin->setAlignment(Qt::AlignCenter);
	jMin->setText("0");
	QRegExp jMinRegExp("[0-9]+$");
	jMinValidator = new QRegExpValidator(jMinRegExp, jMin);
	jMin->setValidator(jMinValidator);
	
	jMax = new QLineEdit();
	jMax->setAlignment(Qt::AlignCenter);
	jMax->setText(QString("%1").arg(image.height()));
	QRegExp jMaxRegExp("[1-9]+$");
	jMaxValidator = new QRegExpValidator(jMaxRegExp, jMax);
	jMax->setValidator(jMaxValidator);

	rMin = new QLineEdit;
	rMin->setAlignment(Qt::AlignCenter);
    rMin->setText(QString("%1").arg(AlgDetect::BIG_CIRCLE_MIN));
	QRegExp rMinRegExp("[1-9]+$");
	rMinValidator = new QRegExpValidator(rMinRegExp, rMin);
	rMin->setValidator(rMinValidator);
	
	rMax = new QLineEdit;
	rMax->setAlignment(Qt::AlignCenter);
    rMax->setText(QString("%1").arg(AlgDetect::BIG_CIRCLE_MAX));
	QRegExp rMaxRegExp("[1-9]+$");
	rMaxValidator = new QRegExpValidator(rMaxRegExp, rMax);
	rMax->setValidator(rMaxValidator);
	
	searchStep = new QLineEdit();
	searchStep->setAlignment(Qt::AlignCenter);
    searchStep->setText(QString("%1").arg(AlgDetect::SEARCH_STEP));
	QRegExp searchStepRegExp("[1-9]+$");
	searchStepValidator = new QRegExpValidator(searchStepRegExp, searchStep);
	searchStep->setValidator(searchStepValidator);

	QHBoxLayout* hLay1 = new QHBoxLayout();
	hLay1->addStretch();
	hLay1->addWidget(iRangeText);
	hLay1->addWidget(iMin);
	hLay1->addWidget(compareMark0);
	hLay1->addWidget(iText);
	hLay1->addWidget(compareMark1);
	hLay1->addWidget(iMax);
	hLay1->addStretch();

	QHBoxLayout* hLay2 = new QHBoxLayout();
	hLay2->addStretch();
	hLay2->addWidget(jRangeText);
	hLay2->addWidget(jMin);
	hLay2->addWidget(compareMark2);
	hLay2->addWidget(jText);
	hLay2->addWidget(compareMark3);
	hLay2->addWidget(jMax);
	hLay2->addStretch();

	QHBoxLayout* hLay3 = new QHBoxLayout();
	hLay3->addStretch();
	hLay3->addWidget(rRangeText);
	hLay3->addWidget(rMin);
	hLay3->addWidget(compareMark4);
	hLay3->addWidget(rText);
	hLay3->addWidget(compareMark5);
	hLay3->addWidget(rMax);
	hLay3->addStretch();

	QHBoxLayout* hLay4 = new QHBoxLayout();
	hLay4->addStretch();
	hLay4->addWidget(searchStepText);
	hLay4->addWidget(searchStep);
	hLay4->addStretch();

	paramOk = new QPushButton("OK");
	connect(paramOk, SIGNAL(clicked()), this, SLOT(HoughTransform()));
	paramReset = new QPushButton("Reset", this);
	connect(paramReset, SIGNAL(clicked()), this, SLOT(ResetParams()));

	QHBoxLayout* hLay5 = new QHBoxLayout();
	hLay5->addStretch();
	hLay5->addWidget(paramOk);
	hLay5->addStretch();
	hLay5->addWidget(paramReset);
	hLay5->addStretch();

	QLabel* cValue = new QLabel("The circle point is");
	QLabel* rValue = new QLabel("The r of the circle is");
	QLabel* aValue = new QLabel("a:");
	QLabel* bValue = new QLabel("b:");

	a = new QLineEdit;
	a->setAlignment(Qt::AlignCenter);
	b = new QLineEdit;
	b->setAlignment(Qt::AlignCenter);
	r = new QLineEdit;
	r->setAlignment(Qt::AlignCenter);

	QHBoxLayout* hLay6 = new QHBoxLayout();
	hLay6->addStretch();
	hLay6->addWidget(cValue);
	hLay6->addWidget(aValue);
	hLay6->addWidget(a);
	hLay6->addWidget(bValue);
	hLay6->addWidget(b);
	hLay6->addWidget(rValue);
	hLay6->addWidget(r);
	hLay6->addStretch();

	QVBoxLayout* vLay = new QVBoxLayout;
	vLay->addLayout(hLay1);
	vLay->addLayout(hLay2);
	vLay->addLayout(hLay3);
	vLay->addLayout(hLay4);
	vLay->addStretch(1);
	vLay->addLayout(hLay5);
	vLay->addLayout(hLay6);

	setLayout(vLay);
	setFixedSize(450, 200);
	setAttribute(Qt::WA_DeleteOnClose);
}

UiHoughTransformParam::~UiHoughTransformParam()
{
	delete iMinValidator;
	delete iMaxValidator;
	delete jMinValidator;
	delete jMaxValidator;
	delete rMinValidator;
	delete rMaxValidator;
	delete searchStepValidator;
};

void UiHoughTransformParam::HoughTransform()
{
	unsigned int iMinValue = iMin->text().toInt();
	unsigned int iMaxValue = iMax->text().toInt();
	unsigned int jMinValue = jMin->text().toInt();
	unsigned int jMaxValue = jMax->text().toInt();
	unsigned int rMinValue = rMin->text().toInt();
	unsigned int rMaxValue = rMax->text().toInt();
	unsigned int step = searchStep->text().toInt();

    AddTransform(new AlgDetect::Hough(img,
																rMinValue, 
																rMaxValue,
																step, 
																iMinValue, 
																iMaxValue, 
																jMinValue, 
																jMaxValue,
																100,
																cle));
}

void UiHoughTransformParam::ResetParams()
{
	iMin->setText("0");
	iMax->setText(QString("%1").arg(img.width()));
	jMin->setText("0");
	jMax->setText(QString("%1").arg(img.height()));
    rMin->setText(QString("%1").arg(AlgDetect::BIG_CIRCLE_MIN));
    rMax->setText(QString("%1").arg(AlgDetect::BIG_CIRCLE_MAX));
    searchStep->setText(QString("%1").arg(AlgDetect::SEARCH_STEP));
	a->setText("");
	b->setText("");
	r->setText("");
}

void UiHoughTransformParam::AddTransform(baseTransform* transform)
{
	subThread->addTransform(transform);
}

void UiHoughTransformParam::ShowResult()
{
	if (cle.hasValue)
	{
		a->setText(QString("%1").arg(cle.a));
		b->setText(QString("%1").arg(cle.b));
		r->setText(QString("%1").arg(cle.r));
	}
	else
	{
		QMessageBox warning(QMessageBox::Warning, "Alert!",  "No circle found under this condition!");
		warning.exec();	
	}
}
