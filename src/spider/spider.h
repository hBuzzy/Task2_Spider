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
        unsigned int velocity = 1,
        QObject *parent = nullptr
    );
public slots:
    int Move(const QPoint&, const QRect&);
    void SetVelocity(int);
    void Draw(QPainter*);
private:
    QPoint pos_;
    QPixmap image_;
    int velocity_;
    LimitedQueue<QPoint, 3> web_;
};

#endif
