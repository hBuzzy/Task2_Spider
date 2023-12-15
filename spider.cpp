#include "spider.h"

Spider::Spider(QObject *parent) : QObject{parent} {
    position_ = QPoint(100, 100);
    speed_  =QPoint(5, 5);
    spiderHeight_ = 84;
    spiderWidth_ = 80;
    maxSpeed_ = 20;
    minSpeed_ = 1;
    speedChange_=5;
}
QPoint Spider::getPosition() {return position_;}
QPoint Spider::getSpiderStep(){return speed_;}
QList<QPoint> Spider::getWebPoints(){return webPoints_;}

void Spider:: moveSpider(int xStep, int yStep) {
    SetWeb(QPoint(xStep,yStep ));
    position_ = QPoint(position_.x() + xStep, position_.y() + yStep);

}
void Spider::speedDown() {
    speed_=QPoint(speed_.x() - speedChange_, speed_.y() - speedChange_);
    if (speed_.x() < minSpeed_) {
        speed_ = QPoint(minSpeed_, minSpeed_);
    }
}
void Spider::speedUp() {
    speed_=QPoint(speed_.x() + speedChange_, speed_.y() + speedChange_);
    if (speed_.x() > maxSpeed_) {
        speed_ = QPoint(maxSpeed_, maxSpeed_);
    }
}
void Spider::SetWeb(QPoint step) {
    webPoints_.append(QPoint(position_.x()+step.x() + spiderWidth_ / 2, position_.y()+step.y() + spiderHeight_ / 2));
}
