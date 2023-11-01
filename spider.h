#ifndef SPIDER_H
#define SPIDER_H

#include <QWidget>

class Spider : public QWidget {
    Q_OBJECT
public:
    explicit Spider(QWidget *widget);

    const int kTime = 50;

    void MoveSpider();
    QPixmap GetRotateImage();
    QPoint GetSpiderPos();
    QVector<QPoint> GetWayPoint();

protected:
    void SetParameters();
    void SetNextPoint();
    int GetRotateAngle();

private:
    QPixmap spiderImage_;
    QPixmap rotatedSpiderImage_;
    QPoint spiderPos_;
    QVector<QPoint> wayPoints_;
    QVector<int> rotateAngles_ = {135, 45, -135, -45};
    QPoint nextWayPoint_;

    int size_;
    int speed_;
    int spiderDirectionX_, spiderDirectionY_;
    int initialRotateAngle_;

    QWidget *widget_;
};

#endif  // SPIDER_H
