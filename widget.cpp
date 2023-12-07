#include "widget.h"

#include <QDateTime>
#include <QDebug>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>

Widget::Widget(QWidget *parent) : QWidget(parent) {
  ellipseMoveTimer_ = new QTimer(this);
  AddToTimerInterval(1000);

  int positionYDivider = 2;
  windowRect_ = rect();
  ellipsePosition_ =
      QPoint(windowRect_.x(), windowRect_.height() / positionYDivider);

  connect(ellipseMoveTimer_, &QTimer::timeout, this, &Widget::ShowMessage);
}

Widget::~Widget() {}

void Widget::ShowMessage() { qDebug() << QDateTime::currentDateTime(); }

void Widget::UpdateEllipsePosition() {
  int dx = 10;

  ellipsePosition_.setX(ellipsePosition_.x() + dx);

  repaint();
}

void Widget::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Space &&
      event->modifiers() == Qt::ControlModifier) {
    spiderMoveTimer_->stop();
  } else {
    spiderMoveTimer_->start();
  }
}

void Widget::resizeEvent(QResizeEvent *event) {
  Q_UNUSED(event);
  windowRect_ = rect();
}

void Widget::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    cursorPosition_ = event->pos();
    isDrawingWeb_ = true;
    ShowMousePosition();
    setCursor(Qt::ClosedHandCursor);
    update();
  }
}

void Widget::mouseMoveEvent(QMouseEvent *event) {
  if (isDrawingWeb_) {
    cursorPosition_ = event->pos();

    if (cursorPosition_.x() < windowRect_.x()) {
      cursorPosition_.setX(0);
    } else if (cursorPosition_.x() > windowRect_.width()) {
      cursorPosition_.setX(width());
    }

    if (cursorPosition_.y() < windowRect_.y()) {
      cursorPosition_.setY(0);
    } else if (cursorPosition_.y() > windowRect_.height()) {
      cursorPosition_.setY(height());
    }

    ShowMousePosition();
    repaint();
  }
}

void Widget::mouseReleaseEvent(QMouseEvent *event) {
  Q_UNUSED(event)
  isDrawingWeb_ = false;
  unsetCursor();
}

void Widget::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  if (ellipseMoveTimer_->isActive()) {
    DrawEllipse(&painter);
  }
}

void Widget::DrawEllipse(QPainter *painter) {
  int width = 20;
  int height = 20;

  painter->setBrush(QBrush(Qt::green));
  painter->drawEllipse(ellipsePosition_, width, height);
}

void Widget::ShowMousePosition() {
  setWindowTitle(QString("x: %1; y: %2;")
                     .arg(cursorPosition_.x())
                     .arg(cursorPosition_.y()));
}

void Widget::AddToTimerInterval(int milliseconds) {
  int minInterval = 100;
  int maxInterval = 1000;

  int newInterval = ellipseMoveTimer_->interval() + milliseconds;

  newInterval = qBound(minInterval, newInterval, maxInterval);

  ellipseMoveTimer_->setInterval(newInterval);
}
