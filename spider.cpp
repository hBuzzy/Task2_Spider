#include "spider.h"
#include <QDebug>

Spider::Spider(const QPoint& position, QObject *parent) : QObject{parent} {
    position_ = position;
    web_.append(position_);
    spiderImage_ = QPixmap("D:/Учеба/4 курс/QT/Task2_Spider/spy.png");
    QSize size(20, 20);
    dx_ = 2;
    dy_ = 2;
    size_ = size;
}

void Spider::DrawSpider(QPainter* painter) {
    QRect rect(position_.x(), position_.y(), size_.width(), size_.height());
    painter->drawPixmap(rect, spiderImage_);
    painter->drawPoints(web_);
}

void Spider::ChangePosition(QRect window) {
  if (window.width() < position_.x() || position_.x() < 0) {
    dx_ *= -1;
  }
  if (window.height() < position_.y() || position_.y() < 0) {
    dy_ *= -1;
  }
}

void Spider::ChangePosition(int x = 1, int y = 1) {
  dx_ = x;
  dy_ = y;
}

void Spider::UpdateSpiderPosition() {
  position_.setX(position_.x() + dx_);
  position_.setY(position_.y() + dy_);
  web_.append(position_);
}
