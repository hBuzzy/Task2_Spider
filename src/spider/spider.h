#ifndef SPIDER_H
#define SPIDER_H

#include <QObject>
#include <QPoint>
#include <QQueue>
#include <QPainter>

#include "limited_queue.hpp"

class Spider : public QObject {
    Q_OBJECT
public:
    explicit Spider(
        QPoint pos,
        const QString& image_path,
        unsigned int velocitySlow = 1,
        unsigned int velocityFast = 3,
        QObject *parent = nullptr
    );
public:
    int Move(const QPoint&, const QRect&);
    void SetVelocity(unsigned int);
    [[nodiscard]] unsigned int GetVelocitySlow() const noexcept;
    [[nodiscard]] unsigned int GetVelocityFast() const noexcept;
    void Draw(QPainter*) const;
private:
    QPoint pos_;
    QPixmap image_;
    const unsigned int velocitySlow_;
    const unsigned int velocityFast_;
    unsigned int velocity_;
    LimitedQueue<QPoint, 3> web_;
};

#endif
