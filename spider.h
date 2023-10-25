#ifndef SPIDER_H
#define SPIDER_H

#include <math.h>

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QObject>
#include <QPainter>
#include <QPixmap>
#include <QPoint>
#include <QTime>

class Spider : public QObject {
  Q_OBJECT

 public:
  Spider(int lag, QPoint position, QObject* parent = nullptr);

  QList<QPoint> GetWeb();
  QPoint GetPosition();
  QPixmap GetImage();
  void Move(int widgetWidth, int widgetHeight);
  void SetLag(int lag);
  int GetLag();

 public slots:
  void MoveSpider();

 signals:
  void SpiderMoved(const QPoint& newPosition);

 private:
  QList<QPoint> web_;
  QPoint position_;
  QPixmap spiderImage_;
  QTimer* timer_;

  int lag_;
  int direction_;
};

#endif  // SPIDER_H
