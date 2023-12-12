#include "widget.h"

#include <QDateTime>
#include <QDebug>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>

Widget::Widget(QWidget *parent) : QWidget(parent) {
  windowRect_ = rect();
  int minStep = 1;
  int maxStep = 100;
  spiderStepX_ = 5;
  spiderStepY_ = 5;
  spiderStepX_ = qBound(minStep, spiderStepX_, maxStep);
  spiderStepY_ = qBound(minStep, spiderStepY_, maxStep);

  spiderWidth_ = 50;
  spiderHeight_ = 50;

  int halthDevider = 2;
  spiderPosition_ = QPoint(windowRect_.width() / halthDevider,
                           windowRect_.height() / halthDevider);

  mySpider_ = new Spider(nullptr, spiderWidth_, spiderHeight_);
  mySpider_->UpdateTrack(spiderPosition_);

  spiderMoveTimer_ = new QTimer(this);
  AddToTimerInterval(100);
  connect(Widget::spiderMoveTimer_, &QTimer::timeout, this,
          &Widget::MoveSpider);
  connect(Widget::spiderMoveTimer_, &QTimer::timeout, this,
          &Widget::ShowMessage);
}

Widget::~Widget() {}

void Widget::ShowMessage() { qDebug() << QDateTime::currentDateTime(); }

void Widget::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Space &&
      event->modifiers() == Qt::ControlModifier) {
    spiderMoveTimer_->stop();
  } else {
    spiderMoveTimer_->start();
    if (event->key() == Qt::Key_Left) {
      moveDirection_ = kLeftDirection_;
    } else if (event->key() == Qt::Key_Right) {
      moveDirection_ = kRightDirection_;
    } else if (event->key() == Qt::Key_Up) {
      moveDirection_ = kUpDirection_;
    } else if (event->key() == Qt::Key_Down) {
      moveDirection_ = kDownDirection_;
    }

    if (event->key() == Qt::Key_Shift) {
      spiderStepX_++;
      spiderStepY_++;
    } else if (event->key() == Qt::Key_Control) {
      spiderStepX_--;
      spiderStepY_--;
    }
  }

  int minStep = 1;
  int maxStep = 100;
  spiderStepX_ = qBound(minStep, spiderStepX_, maxStep);
  spiderStepY_ = qBound(minStep, spiderStepY_, maxStep);
}

void Widget::resizeEvent(QResizeEvent *event) {
  Q_UNUSED(event);
  windowRect_ = rect();
}

void Widget::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  mySpider_->DrawSpider(&painter, spiderPosition_);
  mySpider_->DrawTrack(&painter);
}

void Widget::MoveSpider() {
  int halthDevider = 2;
  int spiderCenterX = spiderWidth_ / halthDevider;
  int spiderCenterY = spiderHeight_ / halthDevider;

  if (moveDirection_ == kLeftDirection_) {
    spiderPosition_.setX(spiderPosition_.x() - spiderStepX_);
  } else if (moveDirection_ == kRightDirection_) {
    spiderPosition_.setX(spiderPosition_.x() + spiderStepX_);
  } else if (moveDirection_ == kUpDirection_) {
    spiderPosition_.setY(spiderPosition_.y() - spiderStepY_);
  } else if (moveDirection_ == kDownDirection_) {
    spiderPosition_.setY(spiderPosition_.y() + spiderStepY_);
  }

  if (spiderPosition_.x() < (windowRect_.x() + spiderCenterX)) {
    spiderPosition_.setX(spiderCenterX);
    moveDirection_ = kRightDirection_;
  } else if (spiderPosition_.x() > (windowRect_.width() - spiderCenterX)) {
    spiderPosition_.setX(windowRect_.width() - spiderCenterX);
    moveDirection_ = kLeftDirection_;
  }

  if (spiderPosition_.y() < (windowRect_.y() + spiderCenterY)) {
    spiderPosition_.setY(spiderCenterY);
    moveDirection_ = kDownDirection_;
  } else if (spiderPosition_.y() > (windowRect_.height() - spiderCenterY)) {
    spiderPosition_.setY(windowRect_.height() - spiderCenterY);
    moveDirection_ = kUpDirection_;
  }

  mySpider_->UpdateTrack(spiderPosition_);
  repaint();
}

void Widget::AddToTimerInterval(int milliseconds) {
  int minInterval = 100;
  int maxInterval = 1000;

  int newInterval = spiderMoveTimer_->interval() + milliseconds;

  newInterval = qBound(minInterval, newInterval, maxInterval);

  spiderMoveTimer_->setInterval(newInterval);
}
