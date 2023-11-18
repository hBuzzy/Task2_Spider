// widget.h
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "spider.h"

class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void moveSpider();
    void speedSliderChanged(int value);
    void spiderPositionChanged(const QPoint &position);
    void updateThreshold(int value);
    void updateLineWidth(int value);
    void setCursorStyle();

private:
    Spider *spider_;
    int speed_;
    QTimer *timer_;
    bool drawing_;
    QPoint center_;
    int lineWidth_;
    QColor lineColor_;

};

#endif // WIDGET_H
