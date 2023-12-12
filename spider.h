#ifndef SPIDER_H
#define SPIDER_H

#include <QObject>
#include <QPainter>
#include <QTimer>

class Spider : public QObject {
  Q_OBJECT
 public:
  Spider(QObject *parent = nullptr, int width = 50, int heigth = 50);

 public:
  void DrawSpider(QPainter *painter, QPoint position);
  void DrawTrack(QPainter *painter);
  void MoveSpider();
  void UpdateTrack(QPoint position);

 private:
  int width_;
  int height_;
  QPixmap pixmap_;
  QVector<QPoint> track_;
};

#endif  // SPIDER_H
