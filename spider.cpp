#include "spider.h"

Spider::Spider(const QPoint& position, QObject *parent) : QObject{parent} {
  position_ = position;
  windowCenter_ = position;
  spiderImage_ = QPixmap("/Users/alepopa/Desktop/учеба/4 курс 1 семестр СПбГАСУ/Букунов. Qt for C++/Spider/meme.png");
  QSize size(40, 40);
  size_ = size;
  web_.append(position_);
  delta_ = 10;
  spin_ = acos(-1) / delta_;
}

void Spider::DrawSpider(QPainter* painter) {
  if (position_.x() < 0 or position_.y() < 0) {
    position_.setX(windowCenter_.x());
    position_.setY(windowCenter_.y());
    spin_ = acos(-1) / delta_;
    web_.clear();
  }

  QRect rect(position_.x(), position_.y(), size_.width(), size_.height());
  painter->drawPixmap(rect, spiderImage_);
}

void Spider::DrawWeb(QPainter* painter) {
  painter->drawPolyline(web_);
}

void Spider::MoveSpider() {
  spin_ += acos(-1) / delta_;
  position_.setX(spin_ * sin(spin_) + windowCenter_.x());
  position_.setY(spin_ * cos(spin_) + windowCenter_.y());
  web_.append(position_);
}
