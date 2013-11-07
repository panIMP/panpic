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
#include "panimagehistproc.h"

class UiHistDialog : public QWidget
{
    Q_OBJECT
public:
    explicit UiHistDialog(PanImage& image, const QString& imageName, QWidget *parent = 0);
    
signals:
    
public slots:
    void Save();

private:
    QPushButton* save;
    PanImage* img;

};

#endif // UIHISTDIALOG_H
