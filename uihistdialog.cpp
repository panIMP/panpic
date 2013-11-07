#include "uihistdialog.h"

UiHistDialog::UiHistDialog(PanImage& image, const QString& imageName, QWidget *parent) :QWidget(parent)
{
    QLabel* histLabel = new QLabel;
    histLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    histLabel->setAlignment(Qt::AlignCenter);
    PanImage histimg = PanImageHistProc::GetInstance()->GetHistImage(image);
    histLabel->setPixmap(QPixmap::fromImage(histimg.PanImage2QImage()));

    img = new PanImage;
    img->SetMat(histimg.GetMat());

    save = new QPushButton("Save", this);
    connect(save, SIGNAL(clicked()), this, SLOT(Save()));

    QVBoxLayout* vLay1 = new QVBoxLayout;
    vLay1->addWidget(histLabel);
    QHBoxLayout* hLay1 = new QHBoxLayout;
    hLay1->addStretch();
    hLay1->addWidget(save);
    hLay1->addStretch();
    vLay1->addLayout(hLay1);
    setLayout(vLay1);
    setWindowTitle("Histogram - " + QFileInfo(imageName).fileName());
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

void UiHistDialog::Save(){
    QString selectedFilter = tr("JPEG(*.jpg *.jpeg)");
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Open File"),
                                                    "../",
                                                    tr("JPEG(*.jpg *.jpeg);; BMP(*.bmp);;"\
                                                       "PNG(*.png);;TIFF(*.tif)"\
                                                       ";;GIF(*.gif);; ICO(*.ico);; ALL(*.*)"
                                                       ),
                                                    &selectedFilter);
    if (fileName != NULL){
        PanImageIO::GetInstance()->SavePanImage(*img, QFileInfo(fileName).absoluteFilePath());
        setWindowModified(false);
        setWindowTitle("Histogram - " + QFileInfo(fileName).fileName());
    }

    delete img;
}
