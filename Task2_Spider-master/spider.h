#ifndef SPIDER_H
#define SPIDER_H

#include <QObject>
#include <QPixmap>

class Spider : public QObject {
  Q_OBJECT
 public:
  explicit Spider(QPixmap, int, QObject *parent = nullptr);
  void SetSpiderCoordinats(QPoint);
  void SetSpiderDestination(QPoint);
  void SetWebPoints(QVector<QPoint>);
  void MoveSpider();
  QPoint GetSpiderCoordinats();
  QPoint GetDestinationPoint();
  QPixmap GetImg();
  QVector<QPoint> GetWebCoordinats();

 private:
  QPixmap spiderImg_;
  QPoint spiderCoordinats_;
  QPoint destinationPoint_;
  int spiderSize_;
  QVector<QPoint> webWayPoints_;
};

#endif  // SPIDER_H
