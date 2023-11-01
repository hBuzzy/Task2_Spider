#include "spider.h"

Spider::Spider(QObject *parent) : QObject{parent} {
    currentPosition_ = QPoint(100,100);
    velocity_ = QPoint(0,0);
}

QList<QLine> Spider::GetWebLines() { return webLines_; }
QPoint Spider::GetCurrentPosition() {return currentPosition_;}

void Spider::SetWeb(const QRect &windowRect) {
    int xMoving = currentPosition_.x() + velocity_.x();
    int yMoving = currentPosition_.y() + velocity_.y();
    if (xMoving > windowRect.width()){
        xMoving = windowRect.width();
        velocity_.setX(-velocity_.x());
    }
    if (xMoving < 0){
        xMoving = 0;
        velocity_.setX(-velocity_.x());
    }
    if (yMoving > windowRect.height()){
        yMoving = windowRect.height();
        velocity_.setY(-velocity_.y());
    }
    if (yMoving < 0){
        yMoving = 0;
        velocity_.setY(-velocity_.y());
    }

    webLines_.append(QLine(currentPosition_, QPoint(xMoving, yMoving)));
    currentPosition_ = QPoint(xMoving, yMoving);
}

void Spider::SetSpeedVector(const QPoint &speedAddValue)
{
    velocity_ = QPoint(velocity_.x() + speedAddValue.x(), velocity_.y() + speedAddValue.y());
}
