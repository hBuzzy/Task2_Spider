#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget {
  Q_OBJECT

 public:
  Widget(QWidget *parent = nullptr);
  ~Widget();

 private slots:
  void ShowMessage();
  void UpdateEllipsePosition();

 protected:
  virtual void mousePressEvent(QMouseEvent *event);
  virtual void paintEvent(QPaintEvent *event);
  virtual void mouseMoveEvent(QMouseEvent *event);
  virtual void mouseReleaseEvent(QMouseEvent *event);
  virtual void resizeEvent(QResizeEvent *event);
  virtual void keyPressEvent(QKeyEvent *event);
  void AddToTimerInterval(int milliseconds);

 private:
  void DrawEllipse(QPainter *painter);
  void ShowMousePosition();

 protected:
  bool isDrawingWeb_;
  QTimer *spiderMoveTimer_;
  QRect windowRect_;
  QPoint cursorPosition_;

 private:
  int timeInterval_;
  QTimer *ellipseMoveTimer_;
  QPoint ellipsePosition_;
};
#endif  // WIDGET_H
