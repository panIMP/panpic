#ifndef QUICKHANDWIDGET_H
#define QUICKHANDWIDGET_H

#include <QWidget>
#include <QSlider>
#include <QLineEdit>
#include <QRegExpValidator>


class QuickHandWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QuickHandWidget(QWidget *parent = 0);

    QString getCurPicIndex();

    static int const ZOOM_RANGE = 240;
    static int const ZOOM_SAME = 120;

signals:
    void zoom(int value);
    void picIndexChanged();

public slots:
    void zoomRateDisp(int value);
    void zoomSliderMove();
    void zoomSliderMove(int value);
    void curPicIndexDisp(int indexVal, int rangeVal);

protected:


private:
    QSlider* m_zoomSlider;
    QLineEdit* m_zoomRateBox;
    QLineEdit *m_curPicIndexBox;
};

#endif // QUICKHANDWIDGET_H
