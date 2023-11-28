// widget.cpp
#include "widget.h"

#include <QPainter>
#include <QSlider>
#include <QVBoxLayout>
#include <QPainter>
#include <QSlider>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QDebug>

Widget::Widget(QWidget *parent) : QWidget(parent), speed_(5), isdrawing_(false) {
    setMouseTracking(true);
    spider_ = new Spider(this);
    connect(spider_, &Spider::positionChanged, this, &Widget::updateSpiderPositionChanged);

    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, &Widget::moveSpider);
    timer_->start(100);

    QSlider *speedSlider = new QSlider(Qt::Horizontal);
    speedSlider->setMinimum(1);
    speedSlider->setMaximum(10);
    speedSlider->setValue(5);
    connect(speedSlider, &QSlider::valueChanged, this, &Widget::setSpeedSliderChanged);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(speedSlider);
    setLayout(layout);

    spider_->startMoving();
}

Widget::~Widget() {
    delete spider_;
}

void Widget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(spider_->getPosition(), spider_->getSpiderImage());

    painter.setPen(QPen(Qt::black, 2));
    for (const QPoint &point : spider_->getPath()) {
        painter.drawPoint(point);
    }
}

void Widget::updateSpiderPositionChanged(const QPoint &position) {
    update();
}

void Widget::setSpeedSliderChanged(int value) {
    speed_ = value;
    spider_->setSpeed(speed_);
}

void Widget::moveSpider() {
    if (isdrawing_) {
            QPoint globalCursorPos = mapToGlobal(center_);
            spider_->moveSpider(globalCursorPos);
        }
}

void Widget::mouseMoveEvent(QMouseEvent *event) {
    if (isdrawing_) {
        center_ = event->pos();

        qDebug() << center_.x() << " " << center_.y();
    }
}

void Widget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        isdrawing_ = true;
        center_ = event->pos();
        setCursorStyle();

        spider_->moveSpider(mapToGlobal(center_));
    }
}

void Widget::updateThreshold(int value) {
  lineColor_.setRed(value);
  setCursorStyle();
  update();
}

void Widget::updateLineWidth(int value) {
  lineWidth_ = value;
  update();
}

void Widget::setCursorStyle() {
  if (isdrawing_) {
    setCursor(Qt::CrossCursor);
  } else {
    setCursor(Qt::ArrowCursor);
  }
}

void Widget::mouseReleaseEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton && isdrawing_) {
    isdrawing_ = false;
    setCursorStyle();
  }
}
