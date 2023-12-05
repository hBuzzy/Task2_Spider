#include "widget.h"

#include <QPixmap>
#include <QPainter>
#include <QTimer>
#include <QDebug>

Widget::Widget(QWidget *parent) : QWidget(parent) {
    sizePoint_ = 3;
    setFixedSize(800, 600);
    spider_ = new Spider(this);

    spider_->SetDirectionX(0);
    spider_->SetDirectionY(0);

    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, &Widget::updateSpiderMovement);
    timer_->start(20);
}

Widget::~Widget() {}

void Widget::updateSpiderMovement() {
    spider_->SetDirectionX((hasRightPressed_ ? 1 : 0) + (hasLeftPressed_ ? -1 : 0));
    spider_->SetDirectionY((hasDownPressed_ ? 1 : 0) + (hasUpPressed_ ? -1 : 0));
    spider_->MoveSpider();
}

void Widget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    QPen pointPen = painter.pen();
    pointPen.setWidth(sizePoint_);
    painter.setPen(pointPen);

    for (QPoint point : spider_->GetWayPoint()) {
        painter.drawPoint(point);
    }
    painter.drawPixmap(spider_->GetSpiderPos(), spider_->GetRotateImage());
    update();
}

void Widget::keyPressEvent(QKeyEvent *event) {

    switch (event->key()) {
    case Qt::Key_Up:
        hasUpPressed_ = true;
        break;
    case Qt::Key_Right:
        hasRightPressed_ = true;
        break;
    case Qt::Key_Down:
        hasDownPressed_ = true;
        break;
    case Qt::Key_Left:
        hasLeftPressed_ = true;
        break;
    }

}

void Widget::keyReleaseEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Up:
        hasUpPressed_ = false;
        break;
    case Qt::Key_Right:
        hasRightPressed_ = false;
        break;
    case Qt::Key_Down:
        hasDownPressed_ = false;
        break;
    case Qt::Key_Left:
        hasLeftPressed_ = false;
        break;
    }
}

QSize Widget::GetSizeWidget() {
    return sizeWidget_ = this->size();
}
