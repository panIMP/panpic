#ifndef UI_HOUGH_DLG_H
#define UI_HOUGH_DLG_H

#include <QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <QtGui/QRegExpValidator>

#include "algDetect.h"
#include "baseTransform.h"
#include "baseThread.h"

class UiHoughDlg :public QWidget
{
	Q_OBJECT

public:
	explicit UiHoughDlg(AlgDetect::_Pan_Circle& circle, baseImage& image, AlgDetect::_Hough_Param& hParam,QWidget* parent = 0);
	~UiHoughDlg();

	void AddTransform(baseTransform* transform);

public slots:
	void ShowResult();

	void HoughTransform();
	void ResetParams();

private:
	baseThread* subThread;

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

	baseImage& image;
	AlgDetect::_Pan_Circle& cle;
	AlgDetect::_Hough_Param& hParam;

	QRegExpValidator* iMinValidator;
	QRegExpValidator* iMaxValidator;
	QRegExpValidator* jMinValidator;
	QRegExpValidator* jMaxValidator;
	QRegExpValidator* rMinValidator;
	QRegExpValidator* rMaxValidator;
	QRegExpValidator* searchStepValidator;
};

#endif
