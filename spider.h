#ifndef SPIDER_H
#define SPIDER_H

#include <QObject>
#include <QPainter>
#include <QWidget>
#include <cmath>

class Spider : public QObject {
  Q_OBJECT
 public:
  explicit Spider(const QPoint& position, QObject *parent = nullptr);

 public slots:
  void MoveSpider();

 public:
  void DrawSpider(QPainter* painter);
  void DrawWeb(QPainter* painter);

 private:
  QPixmap spiderImage_;
  QPoint position_;
  QPoint windowCenter_;
  QList<QPoint> web_;
  QSize size_;
  double spin_;
  double delta_;
};

#endif  // SPIDER_H
