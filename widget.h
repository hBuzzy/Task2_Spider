#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPaintEvent>
#include <QPainter>
#include <QTimer>

class Widget : public QWidget {
  Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void MoveSpider();
    void ParametersSpider();
    void VecPointLine();
    int GetRotateAngle();
    void paintEvent(QPaintEvent *event);

    QPixmap SpiderImage_;
    QPixmap rotatedSpiderImage_;

    QPoint NewPoint_;
    QPoint SpiderPoint_, PointLine_;
    QVector<QPoint> points_;
    QTimer *SpiderTimer_;

    int SizeSpider_;
    int SpiderSpeed_;
    int SpiderDirX_, SpiderDirY_;
    int AngleRotate_;
    int SizePoint_;
    int NumbTimer;
};
#endif  // WIDGET_H
