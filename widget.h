#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "spider.h"

class Widget : public QWidget {
  Q_OBJECT

 public:
  Widget(QWidget *parent = nullptr);
  ~Widget();

  void DrawSpider();

 protected:
  virtual void paintEvent(QPaintEvent *event);
  virtual void resizeEvent(QResizeEvent *event);
  virtual void keyPressEvent(QKeyEvent *event);

 private:
  void updateTimer(int lag);

 private:
  QRect windowRect_;
  QTimer *drawTimer_;
  Spider *spider_;
};
#endif  // WIDGET_H
