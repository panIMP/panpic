#ifndef UI_HOUGHTRANSFORMPARAM_H
#define UI_HOUGHTRANSFORMPARAM_H

#include <QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <QtGui/QRegExpValidator>

#include "panimagedetect.h"
#include "transform.h"
#include "transformthread.h"

class UiHoughTransformParam :public QWidget
{
	Q_OBJECT

public:
	explicit UiHoughTransformParam(_Pan_Circle& circle, PanImage& image, QWidget* parent = 0);
	~UiHoughTransformParam();

	void AddTransform(Transform* transform);

public slots:
	void ShowResult();

	void HoughTransform();
	void ResetParams();

private:
	TransformThread* subThread;

	QPushButton* paramOk;
	QPushButton* paramReset;
	
	QLineEdit* iMin;
	QLineEdit* iMax;
	QLineEdit* jMin;
	QLineEdit* jMax;
	QLineEdit* rMin;
	QLineEdit* rMax;
	QLineEdit* searchStep;
	QLineEdit* a;
	QLineEdit* b;
	QLineEdit* r;

	PanImage& img;
	_Pan_Circle& cle;

	QRegExpValidator* iMinValidator;
	QRegExpValidator* iMaxValidator;
	QRegExpValidator* jMinValidator;
	QRegExpValidator* jMaxValidator;
	QRegExpValidator* rMinValidator;
	QRegExpValidator* rMaxValidator;
	QRegExpValidator* searchStepValidator;
};

#endif
