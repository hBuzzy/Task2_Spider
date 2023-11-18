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
    void moveSpider(const QPoint &target); // Изменим сигнатуру метода

private:
    QTimer *timer_;
    QPixmap spiderImage_;
    QPoint position_;
    int speed_;
    QVector<QPoint> web_;
    QVector<QPoint> path_;

public:
    QVector<QPoint> getPath() const;
};

#endif // SPIDER_H
