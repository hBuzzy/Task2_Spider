// spider.h
#ifndef SPIDER_H
#define SPIDER_H

#include <QObject>
#include <QPixmap>
#include <QTimer>
#include <QPoint>
#include <QVector>

class Spider : public QObject {
    Q_OBJECT
public:
    explicit Spider(QObject *parent = nullptr);

    void setSpeed(int speed);
    void setStartPosition(const QPoint &position);
    void startMoving();
    void stopMoving();

    QPoint getPosition() const;
    QPixmap getSpiderImage() const;

signals:
    void positionChanged(const QPoint &position);

public slots:
    void moveSpider();

private:
    QTimer *_timer;
    QPixmap _spiderImage;
    QPoint _position;
    int _speed;
    QVector<QPoint> _web;
    QVector<QPoint> _path;

public:
     QVector<QPoint> getPath() const;
};

#endif // SPIDER_H
