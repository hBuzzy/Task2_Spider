#ifndef SPIDER_H
#define SPIDER_H

#include <QObject>
#include <QPoint>
#include <QPixmap>
#include <QPoint>

class Spider : public QObject {
  Q_OBJECT
 public:
  explicit Spider(QObject *parent = nullptr);

    QList<QPoint> getWebPoints();
    void moveSpider(int, int);
    QPoint getPosition();
    QPoint getSpiderStep();
    void changeSpeed(int speedChange);
    int getSpeedChange();

 private:
    void SetWeb(QPoint step);

    QPoint position_;
    QPoint speed_;
    QList<QPoint> webPoints_;
    int spiderHeight_;
    int spiderWidth_;
    int maxSpeed_;
    int minSpeed_;
    int speedChange_;
};

#endif  // SPIDER_H
