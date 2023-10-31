#ifndef SPIDER_H
#define SPIDER_H

#include <QObject>
#include <QPainter>
#include <QWidget>
#include <cmath>

class Spider : public QObject
{
  Q_OBJECT
 public:
  explicit Spider(const QPoint& position, QObject *parent = nullptr);
  QPixmap GetImage();
  QPoint GetPosition();
  QList<QPoint> GetWeb();
  QSize GetSize();
  void DrawSpider(QPainter* painter);
  void ChangePosition(QRect window);
  void ChangePosition(int x, int y);
 public slots:
  void UpdateSpiderPosition();


 private:
  QPixmap spiderImage_;
  QPoint position_;
  QList<QPoint> web_;
  QSize size_;
  int dx_;
  int dy_;
};

#endif  // SPIDER_H
