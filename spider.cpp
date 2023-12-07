#include "spider.h"

#include <QDir>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>

Spider::Spider(Widget *parent) : Widget{parent} {
  QString currentPath = QDir::currentPath();
  QString parentPath = currentPath + "/spider5.png";

  spiderPixmap_ = QPixmap(parentPath);

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
  spiderTrack_.append(spiderPosition_);

  spiderMoveTimer_ = new QTimer(this);
  AddToTimerInterval(100);
  connect(Widget::spiderMoveTimer_, &QTimer::timeout, this,
          &Spider::MoveSpider);
}

void Spider::DrawSpider(QPainter *painter, QPoint spiderPosition) {
  int halthDevider = 2;

  QRect rect(spiderPosition.x() - spiderWidth_ / halthDevider,
             spiderPosition.y() - spiderHeight_ / halthDevider, spiderWidth_,
             spiderHeight_);
  painter->drawPixmap(rect, spiderPixmap_);
}

void Spider::DrawTrack(QPainter *painter) {
  int trackCount = spiderTrack_.count();
  int offset = 1;
  if (trackCount > 1) {
    for (int i = 1; i < trackCount; i++) {
      painter->drawLine(spiderTrack_[i - offset], spiderTrack_[i]);
    }
  }
}

void Spider::MoveSpider() {
  int halthDevider = 2;
  int spiderCenterX = spiderWidth_ / halthDevider;
  int spiderCenterY = spiderHeight_ / halthDevider;

  if (spiderMoveDirection_ == "left") {
    spiderPosition_.setX(spiderPosition_.x() - spiderStepX_);
  } else if (spiderMoveDirection_ == "right") {
    spiderPosition_.setX(spiderPosition_.x() + spiderStepX_);
  } else if (spiderMoveDirection_ == "up") {
    spiderPosition_.setY(spiderPosition_.y() - spiderStepY_);
  } else if (spiderMoveDirection_ == "down") {
    spiderPosition_.setY(spiderPosition_.y() + spiderStepY_);
  }

  if (spiderPosition_.x() < (windowRect_.x() + spiderCenterX)) {
    spiderPosition_.setX(spiderCenterX);
    spiderMoveDirection_ = "right";
  } else if (spiderPosition_.x() > (windowRect_.width() - spiderCenterX)) {
    spiderPosition_.setX(windowRect_.width() - spiderCenterX);
    spiderMoveDirection_ = "left";
  }

  if (spiderPosition_.y() < (windowRect_.y() + spiderCenterY)) {
    spiderPosition_.setY(spiderCenterY);
    spiderMoveDirection_ = "down";
  } else if (spiderPosition_.y() > (windowRect_.height() - spiderCenterY)) {
    spiderPosition_.setY(windowRect_.height() - spiderCenterY);
    spiderMoveDirection_ = "up";
  }

  spiderTrack_.append(spiderPosition_);
  repaint();
}

void Spider::keyPressEvent(QKeyEvent *event) {
  Widget::keyPressEvent(event);
  if (event->key() == Qt::Key_Left) {
    spiderMoveDirection_ = "left";
  } else if (event->key() == Qt::Key_Right) {
    spiderMoveDirection_ = "right";
  } else if (event->key() == Qt::Key_Up) {
    spiderMoveDirection_ = "up";
  } else if (event->key() == Qt::Key_Down) {
    spiderMoveDirection_ = "down";
  }

  if (event->key() == Qt::Key_Shift) {
    spiderStepX_++;
    spiderStepY_++;
  } else if (event->key() == Qt::Key_Control) {
    spiderStepX_--;
    spiderStepY_--;
  }
  int minStep = 1;
  int maxStep = 100;
  spiderStepX_ = qBound(minStep, spiderStepX_, maxStep);
  spiderStepY_ = qBound(minStep, spiderStepY_, maxStep);
}

void Spider::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  DrawSpider(&painter, spiderPosition_);
  DrawTrack(&painter);
}

void Spider::AddToTimerInterval(int milliseconds) {
  int minInterval = 100;
  int maxInterval = 1000;

  int newInterval = spiderMoveTimer_->interval() + milliseconds;

  newInterval = qBound(minInterval, newInterval, maxInterval);

  spiderMoveTimer_->setInterval(newInterval);
}

void Spider::resizeEvent(QResizeEvent *event) { Widget::resizeEvent(event); }
