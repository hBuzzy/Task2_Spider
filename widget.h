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

 protected:
  virtual void paintEvent(QPaintEvent* event);
  virtual void keyPressEvent(QKeyEvent *event);

 private slots:
  void ShowMessage();

 private:
  Spider* spider_;
  QRect windowRect_;
  QTimer* spiderMoveTimer_;
};
#endif  // WIDGET_H
