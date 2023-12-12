#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "spider.h"

class Widget : public QWidget {
  Q_OBJECT

 public:
  Widget(QWidget *parent = nullptr);
  ~Widget();

 private slots:
  void ShowMessage();
  void MoveSpider();

 protected:
  virtual void paintEvent(QPaintEvent *event);
  virtual void resizeEvent(QResizeEvent *event);
  virtual void keyPressEvent(QKeyEvent *event);
  void AddToTimerInterval(int milliseconds);

 protected:
  QTimer *spiderMoveTimer_;
  QRect windowRect_;
  QPoint spiderPosition_;

 private:
  int timeInterval_;
  int spiderStepX_;
  int spiderStepY_;
  int spiderWidth_;
  int spiderHeight_;
  Spider *mySpider_;
  QString moveDirection_;
  const QString kRightDirection_ = "right";
  const QString kLeftDirection_ = "left";
  const QString kUpDirection_ = "up";
  const QString kDownDirection_ = "down";
};
#endif  // WIDGET_H
