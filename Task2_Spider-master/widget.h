#ifndef WIDGET_H
#define WIDGET_H

#include <QPainter>
#include <QWidget>

#include "spider.h"
class Widget : public QWidget {
  Q_OBJECT

 public slots:
  void spiderMove();

 public:
  Widget(QWidget *parent = nullptr);
  void DrawWeb(QPoint, int, QPainter *);
  ~Widget();

 private:
  QTimer *timer_;
  Spider *spider_;
  QPoint spiderCoordinats_;
  QPoint destinationPoint_;
  int spiderX_;
  int spiderY_;
  int spiderSize_;
  int speed_;
  int modifier_;
  QVector<QPoint> webWayPoints_;
  bool isUpPressed = false;
  bool isLeftPressed = false;
  bool isRightPressed = false;
  bool isDownPressed = false;
  void CheckDiagonalMovement();

 protected:
  void paintEvent(QPaintEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;
};
#endif  // WIDGET_H
