#ifndef UI_MAIN_WIN_H
#define UI_MAIN_WIN_H

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
#include <QtWidgets/QComboBox>

#include "baseImage.h"
#include "baseThread.h"

#include "algShift.h"
#include "algHistProc.h"
#include "algFilter.h"
#include "algDetect.h"

#include "uiHistDlg.h"
#include "uiHoughDlg.h"


class UiMainWindow : public QMainWindow
{
	Q_OBJECT
	Q_PROPERTY(bool HasImage READ HasImage WRITE SetHasImage NOTIFY ImageLoaded)

public:
	explicit UiMainWindow(QWidget *parent = 0);
	~UiMainWindow();

	bool HasImage() const {return m_hasImage;}
	void SetHasImage(bool value);

	baseImage& Image(){return m_PanImage;}
	void SetImage(baseImage& newImage);

	void InitGlobalVariables();

	void CreateCenterWidget();
	void CreatePicEditorApp();
	void CreatePicSearcherApp();

	void CreateStatusBar();
	void CreateGlobalSigSlotLink();
	void CreateMainWindowStyle();

	void AddTransform(baseTransform* transform);

signals:
	void ImageChanged();
	void ImageLoaded(bool);
	void MouseOnPicWheeled(int);
	void PicIndexSwitched(int, int);

public slots:
	void AllTransformDone();

	void SetImage(int);

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

	void SelectSearchFolder();
	void StartSearch();

protected:
	void dragEnterEvent(QDragEnterEvent *event);
	void dropEvent(QDropEvent* event);
	void wheelEvent(QWheelEvent *event);
	void resizeEvent(QResizeEvent *event);

private:
	// Independent Dialogs
	UiHistDialog* hist;
	UiHoughDlg* houghParamDialog;

	//	Transform threads
	baseThread* subThread;

	//	Signals and const values
	bool m_hasImage;

	//	Center widgets
	QWidget* m_centerWidget;
	QListWidget* m_appList;
	QStackedLayout*m_appFrame;

	//	pic editor app widgets
	QSplitter* m_picEditorSplitter;
	QTabWidget* m_picEditorTabWidget;

	QScrollArea* m_editFrame;
	QLabel* m_editArea;
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
	AlgDetect::_Pan_Circle bigCircle;
	AlgDetect::_Pan_Circle smallCircle;
	AlgDetect::_Hough_Param hParam;

	//	pic searcher app widgets
	QSplitter* m_picSearchSplitter;
	QWidget* m_chooseLine;
	QWidget* m_searchLine;
	QWidget* m_resultLine1;
	QWidget* m_resultLine2;

	QLabel* m_searchArea;
	QLabel* m_traverseArea;
	QLabel* m_resultArea1;
	QLabel* m_resultArea2;
	QLabel* m_resultArea3;
	QLabel* m_resultArea4;
	QLabel* m_resultArea5;
	QLabel* m_resultArea6;
	QLabel* m_resultArea7;
	QLabel* m_resultArea8;
	QPushButton* m_setSearchFolder;
	QPushButton* m_startSearch;
	QComboBox* m_setSearchMethod;

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
	QString m_searchFolder;
	QFileInfoList m_searchFileList;
	QPushButton* m_openPic;
	QPushButton* m_save;
	QPushButton* m_saveAs;
	QPushButton* m_prevPic;
	QPushButton* m_nextPic;
	QLabel* m_curPicWidth;
	QLabel* m_curPicHeight;

	//	shared global variables
	baseImage m_PanImage;
	QImage m_QImage;
};

#endif // MAINWINDOW_H
