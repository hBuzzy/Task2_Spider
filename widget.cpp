#include "widget.h"
#include "spider.h"

#include <QPainter>
#include <QTimer>
#include <QDateTime>

Widget::Widget(QWidget *parent) : QWidget(parent) {
  spider_ = new Spider(QPoint(300, 150));
  spiderMoveTimer_ = new QTimer(this);
  spiderMoveTimer_->setInterval(500);
  windowRect_ = rect();

  connect(spiderMoveTimer_, &QTimer::timeout, this, &Widget::ShowMessage);

  connect(spiderMoveTimer_, &QTimer::timeout, [this](){ spider_->ChangePosition(windowRect_); spider_->UpdateSpiderPosition(); repaint(); });
}

Widget::~Widget() {}

void Widget::paintEvent(QPaintEvent* event) {
  Q_UNUSED(event);
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  spider_->DrawSpider(&painter);
}


void Widget::keyPressEvent(QKeyEvent *event) {
  int deltaTimerInterval = 50;
  windowRect_ = rect();
  int positionFirst = 2;
  int positionSecond = 0;
  if (event->key() == Qt::Key_Space) {
    spiderMoveTimer_->start();
    spider_->ChangePosition(positionFirst, positionFirst);
  } else if (event->key() == Qt::Key_Minus) {
    AddToTimerInterval(deltaTimerInterval);
  } else if (event->key() == Qt::Key_Plus) {
    AddToTimerInterval(-deltaTimerInterval);
  } else if (event->key() == Qt::Key_Down) {
    spider_->ChangePosition(positionSecond, positionFirst);
  } else if (event->key() == Qt::Key_Up) {
    spider_->ChangePosition(positionSecond, -positionFirst);
  } else if (event->key() == Qt::Key_Left) {
      spider_->ChangePosition(-positionFirst, positionSecond);
  } else if (event->key() == Qt::Key_Right) {
      spider_->ChangePosition(positionFirst, positionSecond);
  }
}

void Widget::AddToTimerInterval(int milliseconds) {
  int minInterval = 100;
  int maxInterval = 3000;

  int newInterval = spiderMoveTimer_->interval() + milliseconds;

  newInterval = qBound(minInterval, newInterval, maxInterval);

  spiderMoveTimer_->setInterval(newInterval);
}

void Widget::ShowMessage() { qDebug() << QDateTime::currentDateTime(); }
