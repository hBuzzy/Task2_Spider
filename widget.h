#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include "spider.h"

class Widget : public QWidget
{
  Q_OBJECT

 public:
  Widget(QWidget *parent = nullptr);
  ~Widget();

 private:
  void AddToTimerInterval(int milliseconds);
 private slots:
  void ShowMessage();

 private:
  Spider* spider_;
  QRect windowRect_;
  QTimer* spiderMoveTimer_;

 protected:
  virtual void paintEvent(QPaintEvent* event);
  void keyPressEvent(QKeyEvent *event);
};
#endif  // WIDGET_H
