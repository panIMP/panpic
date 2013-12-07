#ifndef UIHOUGHTRANSFORMPARAM_H
#define UIHOUGHTRANSFORMPARAM_H

#include <QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>

#include "panimagedetect.h"
#include "transform.h"
#include "transformthread.h"

class UiHoughTransformParam :public QWidget
{
	Q_OBJECT

public:
	explicit UiHoughTransformParam(PanImage& image, _Pan_Circle& circle, QWidget* parent = 0);
	
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

	PanImage img;
	_Pan_Circle cle;
};

#endif
