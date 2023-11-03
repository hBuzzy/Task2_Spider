#ifndef WIDGET_H
#define WIDGET_H

#include "spider.h"

#include <QWidget>
#include <QKeyEvent>
#include <QTimer>

class Widget : public QWidget {
  Q_OBJECT

 public:
  Widget(QWidget *parent = nullptr);
  ~Widget();

 protected:
  virtual void paintEvent(QPaintEvent *event);
  virtual void keyPressEvent(QKeyEvent *event);

 private:
  void AddToTimerInterval(int milliseconds);

 private:
  Spider* spider_;
  QTimer* timer_;
  QPoint windowCenter_;
  int minInterval_;
};

#endif  // WIDGET_H
