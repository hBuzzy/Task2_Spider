#include "widget.h"

#include <QPixmap>
#include <QPainter>
#include <QTimer>

Widget::Widget(QWidget *parent) : QWidget(parent) {
    sizePoint_ = 3;
    setFixedSize(800, 600);
    spider_ = new Spider(this);
    SetTimer();
}

Widget::~Widget() {}

void Widget::SetTimer() {
    timer_ = new QTimer(this);
    timer_->setInterval(spider_->kTime);
    connect(timer_, &QTimer::timeout, spider_, &Spider::MoveSpider);
    timer_->start();
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

QSize Widget::GetSizeWidget() {
    return sizeWidget_ = this->size();
}
