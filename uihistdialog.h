#ifndef UIHISTDIALOG_H
#define UIHISTDIALOG_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileInfo>
#include <QPushButton>
#include <QFileDialog>

#include "panimage.h"
#include "panimageio.h"
#include "panimagehist.h"
#include "transformthread.h"

class UiHistDialog : public QWidget
{
	Q_OBJECT
public:
	explicit UiHistDialog(PanImage& image, const QString& imageName, QWidget *parent = 0);
	
	void AddTransform(Transform* transform);

signals:
	
public slots:
	void ShowResult();
	void Save();

private:
	//	Transform threads
	TransformThread* subThread;

	QLabel* histLabel;
	QPushButton* save;
	PanImage histimg;
};

#endif // UIHISTDIALOG_H
