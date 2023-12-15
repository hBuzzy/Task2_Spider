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
    void SetWeb(QPoint step);
    QList<QPoint> SetWebPoints() ;
    void setPosition(QPoint position);
    void moveSpider(int, int);
    void speedUp();
    void speedDown();
    QPoint getPosition();
    QPoint getSpiderStep();

 private:
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
