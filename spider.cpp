// spider.cpp
#include "spider.h"

#include <QDebug>

Spider::Spider(QObject *parent) : QObject(parent), speed_(2) {
    path_.clear();
    if (spiderImage_.load("D:/Task2_Spider/images/spider.png")) {
            qDebug() << "Spider image loaded successfully!";
        } else {
            qDebug() << "Failed to load spider image!";
    }
    position_ = QPoint(50, 50);
    web_ << QPoint(50, 50) << QPoint(100, 50) << QPoint(150, 100) << QPoint(100, 150) << QPoint(50, 150);
    timer_ = new QTimer(this);
}

void Spider::setSpeed(int speed) {
    speed_ = speed;
}

void Spider::setStartPosition(const QPoint &position) {
    position_ = position;
}

void Spider::startMoving() {
    timer_->start(16);
}

void Spider::stopMoving() {
    timer_->stop();
}

QPoint Spider::getPosition() const {
    return position_;
}

QPixmap Spider::getSpiderImage() const {
    return spiderImage_;
}

void Spider::moveSpider(const QPoint &target) {
    const int stepSize = speed_;

    const QPoint direction = target - position_;

    const qreal distance = QLineF(position_, target).length();

    if (distance <= stepSize) {
        position_ = target;
    } else {
        const QPoint normalizedDirection = direction / distance;

        position_ += normalizedDirection * stepSize;
    }

    path_.append(position_);

    emit positionChanged(position_);
}

QVector<QPoint> Spider::getPath() const {
    return path_;
}
