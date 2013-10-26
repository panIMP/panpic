#include "quickhandwidget.h"

#include <QHBoxLayout>
#include <QString>


QuickHandWidget::QuickHandWidget(QWidget *parent) :QWidget(parent)
{
    m_zoomSlider = new QSlider(Qt::Horizontal, this);
    m_zoomSlider->setValue(ZOOM_SAME);
    m_zoomSlider->setMinimum(0);
    m_zoomSlider->setMaximum(ZOOM_RANGE);
    m_zoomSlider->setTickPosition(QSlider::NoTicks);
    m_zoomSlider->setTickInterval(1);

    m_zoomRateBox = new QLineEdit(this);
    m_zoomRateBox->setText("100%");
    m_zoomRateBox->setMaximumWidth(40);
    m_zoomRateBox->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    // use regular expression to restrict the input to be like 'dd%'
    QRegExp zoomRegexp("[0-9]+%$");
    QValidator* zoomValidator = new QRegExpValidator(zoomRegexp, m_zoomRateBox);
    m_zoomRateBox->setValidator(zoomValidator);

    // while valueChanged, send zoom signal by the way to mainwindow for slot
    connect(m_zoomSlider, SIGNAL(valueChanged(int)), this, SIGNAL(zoom(int)));
    // here must use returnPressed to make sure only trigger valuechanged/edit signal
    // after enter pressed
    connect(m_zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(zoomRateDisp(int)));
    connect(m_zoomRateBox, SIGNAL(returnPressed()), this, SLOT(zoomSliderMove()));

    m_curPicIndexBox = new QLineEdit(this);
    m_curPicIndexBox->setText("0/0");
    m_curPicIndexBox->setMaximumWidth(50);
    m_curPicIndexBox->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    // curpic index box value edited --> send signal picIndexChanged for communication with mainwindow
    connect(m_curPicIndexBox, SIGNAL(returnPressed()), this, SIGNAL(picIndexChanged()));

    // use regular expression to restrict the input to be like 'dd/dd'
    // \d should be set as \\d
    // The C++ compiler transforms backslashes in strings. To include a \ in a regexp,
    // enter it twice, i.e. \\.
    // To match the backslash character itself, enter it four times, i.e. \\\\.
    QRegExp picIndexRegexp("^\\d*/\\d*$");
    QValidator* picIndexValidator = new QRegExpValidator(picIndexRegexp, m_curPicIndexBox);
    m_curPicIndexBox->setValidator(picIndexValidator);


    QHBoxLayout* hLay = new QHBoxLayout;

    hLay->addWidget(m_zoomSlider);
    hLay->addWidget(m_zoomRateBox);
    hLay->addWidget(m_curPicIndexBox);

    setLayout(hLay);
}

QString QuickHandWidget::getCurPicIndex(){
    return m_curPicIndexBox->text();
}

void QuickHandWidget::zoomRateDisp(int value){
    float rate;
    if (value < ZOOM_SAME){
        rate = (float(value) / float(ZOOM_SAME)) * 100.0;
        rate = int(rate);
    }else {
        rate = (float(value) / float(ZOOM_SAME));
        rate *= rate;
        rate = int(rate * 100.0);
    }
    m_zoomRateBox->setText(QString("%1%").arg(rate));
}

void QuickHandWidget::zoomSliderMove(){
    QString tmpStr = QString(m_zoomRateBox->text());
    tmpStr.chop(1);
    float value = tmpStr.toFloat() / 100.0;
    m_zoomSlider->setValue(value * ZOOM_SAME);
}

void QuickHandWidget::zoomSliderMove(int value){
    m_zoomSlider->setValue(value);
}

void QuickHandWidget::curPicIndexDisp(int indexVal, int rangeVal){
    m_curPicIndexBox->setText(QString("%1/%2").arg(indexVal + 1).arg(rangeVal));
}
