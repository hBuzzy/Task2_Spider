#include "spider.h"

Spider::Spider(
    QPoint pos,
    const QString& image_path,
    unsigned int velocitySlow,
    unsigned int velocityFast,
    QObject *parent
): QObject{parent}, pos_(pos), image_(image_path),
velocitySlow_(velocitySlow), velocityFast_(velocityFast),
velocity_(velocitySlow) {
    web_.enqueue(pos_);
}

int Spider::Move(const QPoint& dir, const QRect& bounds) {
    auto new_pos = pos_ + dir * static_cast<int>(velocity_);
    int out_of_bounds =
        new_pos.x() < bounds.left() || new_pos.x() > bounds.right() ? 1 :
        new_pos.y() > bounds.bottom() || new_pos.y() < bounds.top() ? 2 : 0;
    if (!out_of_bounds)
        pos_ = new_pos;
    else
        web_.enqueue(pos_);
    return out_of_bounds;
}

void Spider::SetVelocity(unsigned velocity) {
    velocity_ = velocity;
}

void Spider::Draw(QPainter *painter) const {
    painter->drawPixmap(pos_, image_);
    painter->setPen(QPen(Qt::black, 1, Qt::DashDotDotLine));
    painter->drawPolyline(web_);
    painter->drawLine(web_.last(), pos_ + QPoint(
        image_.width() / 2, image_.height() / 2));
}

unsigned int Spider::GetVelocitySlow() const noexcept {
    return velocitySlow_;
}

unsigned int Spider::GetVelocityFast() const noexcept {
    return velocityFast_;
}
