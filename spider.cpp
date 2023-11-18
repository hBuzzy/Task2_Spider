// spider.cpp
#include "spider.h"
#include <QDebug>

Spider::Spider(QObject *parent) : QObject(parent), _speed(2) {
    _path.clear();
    if (_spiderImage.load("D:/Task2_Spider/images/spider.png")) {
            qDebug() << "Spider image loaded successfully!";
        } else {
            qDebug() << "Failed to load spider image!";
    }
    _position = QPoint(50, 50);
    _web << QPoint(50, 50) << QPoint(100, 50) << QPoint(150, 100) << QPoint(100, 150) << QPoint(50, 150);
    _timer = new QTimer(this);
    connect(_timer, &QTimer::timeout, this, &Spider::moveSpider);
}

void Spider::setSpeed(int speed) {
    _speed = speed;
}

void Spider::setStartPosition(const QPoint &position) {
    _position = position;
}

void Spider::startMoving() {
    _timer->start(16);
}

void Spider::stopMoving() {
    _timer->stop();
}

QPoint Spider::getPosition() const {
    return _position;
}

QPixmap Spider::getSpiderImage() const {
    return _spiderImage;
}

void Spider::moveSpider() {
    if (!_web.isEmpty()) {
        const QPoint target = _web.first();
        const int stepSize = _speed;

        const QPoint direction = target - _position;
        const qreal distance = QLineF(_position, target).length();

        if (distance <= stepSize) {
            _position = target;
            _web.removeFirst();
        } else {
            const QPoint normalizedDirection = direction / distance;
            _position += normalizedDirection * stepSize;
        }

        // Сохраняем текущую позицию в векторе
        _path.append(_position);

        emit positionChanged(_position);
    } else {
        _timer->stop();
    }
}

QVector<QPoint> Spider::getPath() const {
    return _path;
}
