#include "spider.h"
#include "widget.h"
#include <QRandomGenerator>

Spider::Spider(QObject *parent) : QObject(parent), speed(2) {
    position = QPoint(250, 250);
    connect(&timer, &QTimer::timeout, this, &Spider::Move);
}

void Spider::Start() {
    if (!timer.isActive()) {
        timer.start(100);
    }
}

void Spider::Stop() {
    if (timer.isActive()) {
        timer.stop();
    }
}

QPoint Spider::GetPosition() const {
    return position;
}

void Spider::IncreaseSpeed() {
    speed += 5;
}

void Spider::DecreaseSpeed() {
    if (speed > 5) {
        speed -= 5;
    }
}

void Spider::Move() {

    int random = QRandomGenerator::global()->bounded(100);

    if (random < 10) {
        int randomX = QRandomGenerator::global()->bounded(-1, 2);
        int randomY = QRandomGenerator::global()->bounded(-1, 2);
        trajectory = QPoint(randomX, randomY);
    }

    position.rx() += speed * trajectory.x();
    position.ry() += speed * trajectory.y();
    emit SpiderMoved(position);
}
