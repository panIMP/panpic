#ifndef UI_HIST_DLG_H
#define UI_HIST_DLG_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileInfo>
#include <QPushButton>
#include <QFileDialog>

#include "baseImage.h"
#include "algHistProc.h"
#include "baseThread.h"

class UiHistDialog : public QWidget
{
	Q_OBJECT
public:
	explicit UiHistDialog(baseImage& image, const QString& imageName, QWidget *parent = 0);
	
	void AddTransform(baseTransform* transform);

signals:
	
public slots:
	void ShowResult();
	void Save();

private:
	//	Transform threads
	baseThread* subThread;

	QLabel* histLabel;
	QPushButton* save;
	baseImage histimg;
};

#endif // UIHISTDIALOG_H
