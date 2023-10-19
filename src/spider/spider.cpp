#include "spider.h"

Spider::Spider(
    QPoint pos,
    const QString& image_path,
    unsigned int velocity,
    QObject *parent
): QObject{parent}, pos_(pos), image_(image_path),
velocity_(static_cast<int>(velocity)) {
    web_.enqueue(pos_);
}

int Spider::Move(const QPoint& dir, const QRect& bounds) {
    auto new_pos = pos_ + dir * velocity_;
    int out_of_bounds =
        new_pos.x() < bounds.left() || new_pos.x() > bounds.right() ? 1 :
        new_pos.y() > bounds.bottom() || new_pos.y() < bounds.top() ? 2 : 0;
    if (!out_of_bounds)
        pos_ = new_pos;
    else
        web_.enqueue(pos_);
    return out_of_bounds;
}

void Spider::SetVelocity(int velocity) {
    velocity_ = velocity;
}

void Spider::Draw(QPainter *painter) {
    painter->drawPixmap(pos_, image_);
    painter->setPen(QPen(Qt::black, 1, Qt::DashDotDotLine));
    painter->drawPolyline(web_);
    painter->drawLine(web_.last(), pos_ + QPoint(
        image_.width() / 2, image_.height() / 2));
}
