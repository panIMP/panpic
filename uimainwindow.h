#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtCore/QString>
#include <QtWidgets/QAction>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtGui/QImage>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QToolBar>
#include <QtCore/QFileInfoList>
#include <QObject>
#include <QtGui/QWheelEvent>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QSlider>
#include <QtWidgets/QLineEdit>
#include <QtGui/QRegExpValidator>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtGui//QMatrix>
#include <QtGui/QIcon>
#include <QtCore/QtMath>
#include <QtCore/QDir>
#include <QApplication>
#include <QtCore/QUrl>
#include <QtCore/QMimeData>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QDialog>
#include <QtWidgets/QStackedLayout>
#include <QtWidgets/QListWidget>

#include "panimage.h"
#include "panimageio.h"
#include "panimageshift.h"
#include "panimagehist.h"
#include "uihistdialog.h"
#include "panimagefilter.h"
#include "uihoughtransformparam.h"
#include "panimagedetect.h"
#include "transformthread.h"

class UiMainWindow : public QMainWindow
{
	Q_OBJECT
	Q_PROPERTY(bool HasImage READ HasImage WRITE SetHasImage NOTIFY ImageLoaded)

public:
	explicit UiMainWindow(QWidget *parent = 0);
	~UiMainWindow();

	bool HasImage() const {return m_hasImage;}
	void SetHasImage(bool value);

	PanImage& Image(){return m_PanImage;}
	void SetImage(PanImage& newImage);

	void InitGlobalVariables();

	void CreateCenterWidget();
	void CreatePicEditorApp();
	void CreatePicSearcherApp();

	void CreateStatusBar();

	void CreateGlobalSigSlotLink();
	
	void CreateMainWindowStyle();


	void AddTransform(Transform* transform);

signals:
	void ImageChanged();
	void ImageLoaded(bool);
	void MouseOnPicWheeled(int);
	void PicIndexSwitched(int, int);

public slots:
	void AllTransformDone();

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
	void Enhance();

	void Gray();
	void OtsuBinary();
	void SobelSharpen();
	void LaplaceSharpen();
	void MedianBlur();
	void GuassinBlur();
	void MedianFilter();
	void Dilate();
	void Erode();
	void HoleFill();
	void Engrave();
	void Negative();
	void ComFog();
	void Sketch();

	void HoughTransform();

	void CircleIncisionDetection();

protected:
	void dragEnterEvent(QDragEnterEvent *event);
	void dropEvent(QDropEvent* event);
	void wheelEvent(QWheelEvent *event);


private:
	// Independent Dialogs
	UiHistDialog* hist;
	UiHoughTransformParam* houghParamDialog;

	//	Transform threads
	TransformThread* subThread;

	//	Signals and const values
	bool m_hasImage;

	static const int m_minWidth = 800;
	static const int m_minHeight = 600;

	//	Center widgets
	QWidget* m_centerWidget;
	QListWidget* m_appList;
	QStackedLayout*m_appFrame;

	//	pic editor app widgets
	QSplitter* m_picEditorSplitter;
	QTabWidget* m_picEditorTabWidget;

	QScrollArea* m_dispFrame;
	QLabel* m_dispArea;
	PanImage m_PanImage;
	QImage m_QImage;
	QWidget* m_shift_tab;
	QPushButton* m_rotateClkwise;
	QPushButton* m_rotateCntrClkwise;
	QPushButton* m_mirrorH;
	QPushButton* m_mirrorV;
	QWidget* m_hist_tab;
	QPushButton* m_dispHist;
	QPushButton* m_histEqualize;
	QPushButton* m_histMatch;
	QPushButton* m_enhance;
	QWidget* m_filter_tab;
	QPushButton* m_gray;
	QPushButton* m_guassinBlur;
	QPushButton* m_medianBlur;
	QPushButton* m_medianFilter;
	QPushButton* m_sobelSharpen;
	QPushButton* m_laplaceSharpen;
	QPushButton* m_dilate;
	QPushButton* m_erode;
	QPushButton* m_otsuBinary;
	QPushButton* m_holeFill;
	QPushButton* m_engrave;
	QPushButton* m_negative;
	QPushButton* m_comFog;
	QPushButton* m_sketch;
	QWidget* m_detect_tab;
	QPushButton* m_houghTransform;
	QWidget* m_integrated_tab;
	QPushButton* m_cicle_incision_detect;
	_Pan_Circle bigCircle;
	_Pan_Circle smallCircle;

	//	pic searcher app widgets
	QSplitter* m_picSearcherSplitter;
	QTabWidget* m_picSearcherTabWidget;


	//	Status bar
	QStatusBar* m_statusBar;
	QLineEdit* m_zoomRateBox;
	static int const ZOOM_SAME = 100;
	QValidator* zoomValidator;
	QValidator* picIndexValidator;
	QLineEdit* m_curPicIndexBox;
	int m_curFileIndex;
	int m_curFileRange;
	QFileInfoList m_curFileList;
	QString m_fileName;
	QPushButton* m_openPic;
	QPushButton* m_save;
	QPushButton* m_saveAs;
	QPushButton* m_prevPic;
	QPushButton* m_nextPic;
	QLabel* m_curPicWidth;
	QLabel* m_curPicHeight;
};

#endif // MAINWINDOW_H
