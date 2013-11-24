#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

#include "panimagefilter.h"

class UiHoughTransformParam :public QWidget
{
	Q_OBJECT

public:
	explicit UiHoughTransformParam(PanImage& image, _Pan_Circle& circle, QWidget* parent = 0);
	
public slots:
	void HoughTransform();
	void ResetParams();

private:
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

