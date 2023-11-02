#include "spider.h"

Spider::Spider(int maxX, int maxY) {
    isDown_ = false;
    isUp_ = false;
    isLeft_ = false;
    isRight_ = false;

    x_ = maxX/2;
    y_ = maxY/2;

    points_ = new QVector<QPoint>();
}

void Spider::paint(QWidget *ctx) {
    QPainter painter(ctx);
    QPixmap spider = QPixmap(":/img/spider.png");

    QPen pen = QPen(Qt::black);
    pen.setWidth(kStep);
    painter.setPen(pen);

    for (QPoint point : *points_) {
        painter.drawPoint(point);
    }

    painter.rotate(0);
    painter.drawPixmap(x_ - (kStep * 20) / 2, y_ + 0, kStep * 20, kStep * 20, spider);

}

void Spider::addPoint() {
    x_ += isRight_ * kStep + isLeft_ * -1 * kStep;
    y_ += isDown_ * kStep + isUp_ * -1 * kStep;

    points_->push_back({ x_, y_ });
}

void Spider::updateState(QKeyEvent *event, bool state) {
    switch (event->key()) {
        case Qt::Key_Right:
            isRight_ = state;
            break;
        case Qt::Key_Left:
            isLeft_ = state;
            break;
        case Qt::Key_Down:
            isDown_ = state;
            break;
        case Qt::Key_Up:
            isUp_ = state;
            break;
    }
}

Spider::~Spider() {
    delete points_;
}
