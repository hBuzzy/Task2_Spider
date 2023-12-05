#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QKeyEvent>

#include "spider.h"

class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void updateSpiderMovement();

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    QSize GetSizeWidget();

private:
    QPixmap image_;
    QSize sizeWidget_;
    QTimer *timer_;
    int sizePoint_;
    int time_;

    bool hasUpPressed_ = false;
    bool hasDownPressed_ = false;
    bool hasRightPressed_ = false;
    bool hasLeftPressed_ = false;

    Spider *spider_;
};
#endif  // WIDGET_H
