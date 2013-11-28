#ifndef UIMAINWINDOW_H
#define UIMAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QImage>
#include <QLabel>
#include <QScrollArea>
#include <QToolBar>
#include <QFileInfoList>
#include <QObject>
#include <QWheelEvent>
#include <QTabWidget>
#include <QSlider>
#include <QLineEdit>
#include <QRegExpValidator>
#include <QStatusBar>
#include <QPushButton>
#include <QFileDialog>
#include <QString>
#include <QHBoxLayout>
#include <QMatrix>
#include <QIcon>
#include <QtMath>
#include <QDir>
#include <QApplication>
#include <QUrl>
#include <QMimeData>
#include <QSplitter>
#include <QDialog>

#include "panimage.h"
#include "panimageio.h"
#include "panimageshift.h"
#include "panimagehistproc.h"
#include "uihistdialog.h"
#include "panimagefilter.h"
#include "uihoughtransformparam.h"
#include "panimagedetect.h"
#include "panimageintegratedalg.h"

class UiMainWindow : public QMainWindow
{
	Q_OBJECT
	Q_PROPERTY(bool HasImage READ HasImage WRITE SetHasImage NOTIFY ImageLoaded)

public:
	explicit UiMainWindow(const QString& fileName = 0, QWidget *parent = 0);

	bool HasImage() const {return m_hasImage;}
	void SetHasImage(bool value);

	PanImage& Image(){return m_PanImage;}
	void SetImage(PanImage& newImage);

	void CreateTabWidgets();
	void CreatePicDispWidgets(const QString& fileName = 0);
	void CreateCenterWidget(const QString& fileName = 0);
	void CreateStatusBar();
	void CreateGlobalSigSlotLink();
	void CreateMainWindowStyle();
	void CreateOthers();

signals:
	void ImageChanged();
	void ImageLoaded(bool);
	void MouseOnPicWheeled(int);
	void PicIndexSwitched(int, int);

public slots:
	void OpenPic();
	void NextPic();
	void PrevPic();
	void Save();
	void SaveAs();

	void RotateClkwise();
	void RotateCntrClkwise();
	void MirrorH();
	void MirrorV();

	void ZoomPic(int curValue);
	void ZoomPic();
	void ZoomRateDisp(int value);

	void ShowCurIndexPic();
	void ShowCurPicIndex(int, int);

	void EqualizeHist();
	void MatchHist();
	void CreateHistDialog();

	void Gray();
	void OtsuBinary();
	void GradSharpen();
	void MedianBlur();
	void GuassinBlur();
	void MedianFilter();
	void Dilate();
	void Erode();
	void HoleFill();
	void Engrave();
	void Negative();

	void HoughTransform();

	void CircleIncisionDetection();

protected:
	bool eventFilter(QObject* watched, QEvent* event);
	void wheelEvent(QWheelEvent *event);


private:
	// Signals and const values
	bool m_hasImage;

	static const int m_minWidth = 800;
	static const int m_minHeight = 600;

	// Tab tool bars
	QSplitter* m_centerSplitter;
	QTabWidget* m_tabWidget;

	QWidget* m_shift_tab;
	QPushButton* m_rotateClkwise;
	QPushButton* m_rotateCntrClkwise;
	QPushButton* m_mirrorH;
	QPushButton* m_mirrorV;
	QWidget* m_hist_tab;
	QPushButton* m_dispHist;
	QPushButton* m_histEqualize;
	QPushButton* m_histMatch;
	QWidget* m_filter_tab;
	QPushButton* m_gray;
	QPushButton* m_guassinBlur;
	QPushButton* m_medianBlur;
	QPushButton* m_medianFilter;
	QPushButton* m_gradSharpen;
	QPushButton* m_dilate;
	QPushButton* m_erode;
	QPushButton* m_otsuBinary;
	QPushButton* m_holeFill;
	QPushButton* m_engrave;
	QPushButton* m_negative;
	QWidget* m_detect_tab;
	QPushButton* m_houghTransform;
	QWidget* m_integrated_tab;
	QPushButton* m_cicle_incision_detect;

	// Status bar
	QStatusBar* m_statusBar;
	QLineEdit* m_zoomRateBox;
	static int const ZOOM_SAME = 100;
	QLineEdit* m_curPicIndexBox;
	QPushButton* m_openPic;
	QPushButton* m_save;
	QPushButton* m_saveAs;
	QPushButton* m_prevPic;
	QPushButton* m_nextPic;

	// Picture display area components
	QScrollArea* m_dispFrame;
	QLabel* m_dispArea;

	// Image to be processed
	PanImage m_PanImage;
	QImage m_QImage;
	QFileInfoList m_curFileList;
	QString m_fileName;
	int m_curFileIndex;
	int m_curFileRange;
};

#endif // MAINWINDOW_H
