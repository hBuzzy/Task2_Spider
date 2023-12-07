#ifndef SPIDER_H
#define SPIDER_H

#include <QObject>
#include <QPainter>
#include <QTimer>

#include "widget.h"

class Spider : public Widget {
  Q_OBJECT
 public:
  explicit Spider(Widget *parent = nullptr);

 public:
  void DrawSpider(QPainter *painter, QPoint spiderPosition);
  void MoveSpider();

 private:
  void paintEvent(QPaintEvent *event);
  void resizeEvent(QResizeEvent *event);
  void keyPressEvent(QKeyEvent *event);
  void AddToTimerInterval(int milliseconds);
  void DrawTrack(QPainter *painter);

 private:
  int timeInterval_;
  int spiderStepX_;
  int spiderStepY_;
  int spiderWidth_;
  int spiderHeight_;
  QPixmap spiderPixmap_;
  QPoint spiderPosition_;
  QString spiderMoveDirection_;
  QVector<QPoint> spiderTrack_;

 signals:
};

#endif  // SPIDER_H
