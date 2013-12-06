#include "uihoughtransformparam.h"


UiHoughTransformParam::UiHoughTransformParam(PanImage& image, _Pan_Circle& circle, QWidget* parent) : QWidget(parent)
{
	image.copyTo(img);
	cle = circle;

	QLabel* iRangeText = new QLabel("x range is");
	QLabel* iText = new QLabel("x");
	QLabel* jRangeText = new QLabel("y range is");
	QLabel* jText = new QLabel("y");
	QLabel* rRangeText = new QLabel("r range is");
	QLabel* rText = new QLabel("r");
	QLabel* compareMark0 = new QLabel(" < ");
	QLabel* compareMark1 = new QLabel(" < ");
	QLabel* compareMark2 = new QLabel(" < ");
	QLabel* compareMark3 = new QLabel(" < ");
	QLabel* compareMark4 = new QLabel(" < ");
	QLabel* compareMark5 = new QLabel(" < ");
	QLabel* searchStepText = new QLabel("search step is");

	iMin = new QLineEdit;
	iMin->setAlignment(Qt::AlignCenter);
	iMin->setText("0");
	iMax = new QLineEdit;
	iMax->setAlignment(Qt::AlignCenter);
	iMax->setText(QString("%1").arg(PanImageDetect::WIDTH));
	jMin = new QLineEdit;
	jMin->setAlignment(Qt::AlignCenter);
	jMin->setText("0");
	jMax = new QLineEdit;
	jMax->setAlignment(Qt::AlignCenter);
	jMax->setText(QString("%1").arg(PanImageDetect::HEIGHT));
	rMin = new QLineEdit;
	rMin->setAlignment(Qt::AlignCenter);
	rMin->setText(QString("%1").arg(PanImageDetect::BIG_CIRCLE_MIN));
	rMax = new QLineEdit;
	rMax->setAlignment(Qt::AlignCenter);
	rMax->setText(QString("%1").arg(PanImageDetect::BIG_CIRCLE_MAX));
	searchStep = new QLineEdit;
	searchStep->setAlignment(Qt::AlignCenter);
	searchStep->setText(QString("%1").arg(PanImageDetect::SEARCH_STEP));

	QHBoxLayout* hLay1 = new QHBoxLayout;
	hLay1->addStretch();
	hLay1->addWidget(iRangeText);
	hLay1->addWidget(iMin);
	hLay1->addWidget(compareMark0);
	hLay1->addWidget(iText);
	hLay1->addWidget(compareMark1);
	hLay1->addWidget(iMax);
	hLay1->addStretch();

	QHBoxLayout* hLay2 = new QHBoxLayout;
	hLay2->addStretch();
	hLay2->addWidget(jRangeText);
	hLay2->addWidget(jMin);
	hLay2->addWidget(compareMark2);
	hLay2->addWidget(jText);
	hLay2->addWidget(compareMark3);
	hLay2->addWidget(jMax);
	hLay2->addStretch();

	QHBoxLayout* hLay3 = new QHBoxLayout;
	hLay3->addStretch();
	hLay3->addWidget(rRangeText);
	hLay3->addWidget(rMin);
	hLay3->addWidget(compareMark4);
	hLay3->addWidget(rText);
	hLay3->addWidget(compareMark5);
	hLay3->addWidget(rMax);
	hLay3->addStretch();

	QHBoxLayout* hLay4 = new QHBoxLayout;
	hLay4->addStretch();
	hLay4->addWidget(searchStepText);
	hLay4->addWidget(searchStep);
	hLay4->addStretch();

	paramOk = new QPushButton("OK", this);
	connect(paramOk, SIGNAL(clicked()), this, SLOT(HoughTransform()));
	paramReset = new QPushButton("Reset", this);
	connect(paramReset, SIGNAL(clicked()), this, SLOT(ResetParams()));

	QHBoxLayout* hLay5 = new QHBoxLayout;
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

	QHBoxLayout* hLay6 = new QHBoxLayout;
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
	vLay->addLayout(hLay5);
	vLay->addStretch(1);
	vLay->addLayout(hLay6);

	setLayout(vLay);
	setFixedSize(400, 200);
}

void UiHoughTransformParam::HoughTransform()
{
	unsigned int iMinValue = iMin->text().toInt();
	unsigned int iMaxValue = iMax->text().toInt();
	unsigned int jMinValue = jMin->text().toInt();
	unsigned int jMaxValue = jMax->text().toInt();
	unsigned int rMinValue = rMin->text().toInt();
	unsigned int rMaxValue = rMax->text().toInt();
	unsigned int step = searchStep->text().toInt();

	cle = PanImageDetect::GetInstance()->HoughTransform(img, 
														rMinValue, 
														rMaxValue,
														step, 
														iMinValue, 
														iMaxValue, 
														jMinValue, 
														jMaxValue,
														100);
	
	a->setText(QString("%1").arg(cle.a));
	b->setText(QString("%1").arg(cle.b));
	r->setText(QString("%1").arg(cle.r));
}

void UiHoughTransformParam::ResetParams()
{
	iMin->setText("0");
	iMax->setText(QString("%1").arg(PanImageDetect::WIDTH));
	jMin->setText("0");
	jMax->setText(QString("%1").arg(PanImageDetect::HEIGHT));
	rMin->setText(QString("%1").arg(PanImageDetect::BIG_CIRCLE_MIN));
	rMax->setText(QString("%1").arg(PanImageDetect::BIG_CIRCLE_MAX));
	searchStep->setText(QString("%1").arg(PanImageDetect::SEARCH_STEP));
	a->setText("");
	b->setText("");
	r->setText("");
}