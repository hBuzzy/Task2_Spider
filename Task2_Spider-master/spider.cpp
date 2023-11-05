#include <spider.h>
Spider::Spider(QPixmap img, int spiderSize, QObject *parent) : QObject{parent} {
  this->spiderImg_ = img;
  this->spiderSize_ = spiderSize;
}

void Spider::SetSpiderCoordinats(QPoint spiderCoord) {
  this->spiderCoordinats_ = spiderCoord;
}

void Spider::SetSpiderDestination(QPoint destinationPoint) {
  this->destinationPoint_ = destinationPoint;
}

void Spider::SetWebPoints(QVector<QPoint> newWebVec) {
  webWayPoints_ = newWebVec;
}

void Spider::MoveSpider() {
  int spiderX = spiderCoordinats_.x();
  int spiderY = spiderCoordinats_.y();

  if (spiderX > destinationPoint_.x()) {
    spiderX -= 1;

  } else if (spiderX == destinationPoint_.x()) {
    if (spiderY > destinationPoint_.y()) {
      spiderY -= 1;

    } else {
      spiderY += 1;
    }

  } else {
    spiderX += 1;
  }

  spiderCoordinats_.setX(spiderX);
  spiderCoordinats_.setY(spiderY);
}

QPoint Spider::GetSpiderCoordinats() { return spiderCoordinats_; }
QPoint Spider::GetDestinationPoint() { return destinationPoint_; }
QPixmap Spider::GetImg() { return spiderImg_; }

QVector<QPoint> Spider::GetWebCoordinats() { return webWayPoints_; }
