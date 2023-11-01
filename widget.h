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
    void SetTimer();
    void paintEvent(QPaintEvent *event);
    QSize GetSizeWidget();

private:
    QPixmap image_;
    QSize sizeWidget_;
    QTimer *timer_;
    int sizePoint_;
    int time_;

    Spider *spider_;
};
#endif  // WIDGET_H
