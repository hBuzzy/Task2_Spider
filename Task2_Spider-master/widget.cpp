#include "widget.h"

#include <QRandomGenerator>
#include <QTimer>
#include <QWheelEvent>

#include "web.h"
void Widget::DrawWeb(QPoint center, int radius, QPainter *painter) {
  Web b(center, radius, painter);
}
void Widget::spiderMove() {
  spider_->MoveSpider();
  update();
}

Widget::Widget(QWidget *parent) : QWidget(parent) {
  spiderSize_ = 40;
  speed_ = 50;
  modifier_ = 2;
  QPixmap spiderPix(":/img/img/spider.bmp");
  spider_ = new Spider(spiderPix, spiderSize_);

  timer_ = new QTimer(this);
  timer_->start();
  timer_->setInterval(speed_);

  spiderCoordinats_.setX(
      QRandomGenerator::global()->bounded(0, width() - spiderSize_));
  spiderCoordinats_.setY(
      QRandomGenerator::global()->bounded(0, height() - spiderSize_));
  spider_->SetSpiderCoordinats(spiderCoordinats_);

  destinationPoint_.setX(
      QRandomGenerator::global()->bounded(0, width() - spiderSize_));
  destinationPoint_.setY(
      QRandomGenerator::global()->bounded(0, height() - spiderSize_));
  spider_->SetSpiderDestination(destinationPoint_);

  connect(timer_, SIGNAL(timeout()), this, SLOT(spiderMove()));
}

void Widget::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event)
  setWindowTitle("Паучок");
  QPainter painter;

  spiderCoordinats_ = spider_->GetSpiderCoordinats();
  destinationPoint_ = spider_->GetDestinationPoint();

  int destinationPoint_Rad = 5;
  painter.begin(this);
  painter.setBrush(QBrush(QColor(255, 0, 0)));
  painter.drawEllipse(QRect(destinationPoint_.x() - destinationPoint_Rad,
                            destinationPoint_.y() - destinationPoint_Rad,
                            2 * destinationPoint_Rad,
                            2 * destinationPoint_Rad));
  painter.end();

  painter.begin(this);
  int radius = 30;
  painter.drawPixmap(spiderCoordinats_.x(), spiderCoordinats_.y(), spiderSize_,
                     spiderSize_, spider_->GetImg());
  int half = 2;
  double halfSpiderSize = spiderSize_ / half;
  if (spiderCoordinats_.x() == destinationPoint_.x() &&
      spiderCoordinats_.y() == destinationPoint_.y()) {
    destinationPoint_.setX(destinationPoint_.x() + halfSpiderSize);
    destinationPoint_.setY(destinationPoint_.y() + halfSpiderSize);
    webWayPoints_ = spider_->GetWebCoordinats();
    webWayPoints_.append(destinationPoint_);
    spider_->SetWebPoints(webWayPoints_);
    destinationPoint_.setX(
        QRandomGenerator::global()->bounded(0, width() - spiderSize_));
    destinationPoint_.setY(
        QRandomGenerator::global()->bounded(0, height() - spiderSize_));
    spider_->SetSpiderDestination(destinationPoint_);
  }

  for (int i = 0; i < webWayPoints_.size(); i++) {
    DrawWeb(webWayPoints_[i], radius, &painter);
  }

  painter.end();
}

void Widget::wheelEvent(QWheelEvent *event) {
  QPoint angle = event->angleDelta();
  QPoint pixels = event->pixelDelta();

  if (!angle.isNull() && speed_ >= 0) {
    if (angle.y() < 0) {
      speed_ += modifier_;
    } else {
      speed_ -= modifier_;
    }
  } else if (!pixels.isNull() && speed_ >= 0) {
    if (pixels.y() < 0) {
      speed_ += modifier_;
    } else {
      speed_ -= modifier_;
    }
  }

  if (speed_ < 0) speed_ = 1;
  timer_->setInterval(speed_);
  event->accept();
}

void Widget::keyPressEvent(QKeyEvent *event) {
  timer_->stop();
  if (event->key() == Qt::Key_Space) {
    timer_->stop();
  }
  if (event->key() == Qt::Key_Up) {
    isUpPressed = true;
    CheckDiagonalMovement();
  } else if (event->key() == Qt::Key_Left) {
    isLeftPressed = true;
    CheckDiagonalMovement();
  } else if (event->key() == Qt::Key_Right) {
    isRightPressed = true;
    CheckDiagonalMovement();
  } else if (event->key() == Qt::Key_Down) {
    isDownPressed = true;
    CheckDiagonalMovement();
  }
  event->accept();
  update();
}

void Widget::keyReleaseEvent(QKeyEvent *event) {
  if (event->key() != Qt::Key_Space) {
    timer_->start(speed_);
  }

  if (event->key() == Qt::Key_Up) {
    isUpPressed = false;
  } else if (event->key() == Qt::Key_Left) {
    isLeftPressed = false;
  } else if (event->key() == Qt::Key_Right) {
    isRightPressed = false;
  } else if (event->key() == Qt::Key_Down) {
    isDownPressed = false;
  }

  event->accept();
}

void Widget::CheckDiagonalMovement() {
  spiderX_ = spider_->GetSpiderCoordinats().x();
  spiderY_ = spider_->GetSpiderCoordinats().y();
  if (isUpPressed) {
    spiderY_ -= 1;
  } else if (isDownPressed) {
    spiderY_ += 1;
  } else if (isLeftPressed) {
    spiderX_ -= 1;
  } else if (isRightPressed) {
    spiderX_ += 1;
  }

  if (isUpPressed && isLeftPressed) {
    spiderY_ -= 1;
    spiderX_ -= 1;
  }
  if (isUpPressed && isRightPressed) {
    spiderY_ -= 1;
    spiderX_ += 1;
  }
  if (isDownPressed && isLeftPressed) {
    spiderY_ += 1;
    spiderX_ -= 1;
  }
  if (isDownPressed && isRightPressed) {
    spiderY_ += 1;
    spiderX_ += 1;
  }
  spider_->SetSpiderCoordinats(QPoint(spiderX_, spiderY_));
}

Widget::~Widget() {}
