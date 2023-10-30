#ifndef SPIDER_H
#define SPIDER_H

#include <QPainter>

class Spider : public QObject {
  Q_OBJECT

 public:
  Spider(int lag, QPoint position, QObject* parent = nullptr);

  QList<QPoint> GetWeb();
  QPoint GetPosition();
  QPoint ConstrainPointToBounds(QPoint point, int widgetWidth,
                                int widgetHeight);
  QPoint CalculateNewPosition(int widgetWidth, int widgetHeight);
  QPixmap GetImage();
  void Move(int widgetWidth, int widgetHeight);
  void SetLag(int lag);
  int GetLag();

 private:
  QList<QPoint> web_;
  QPoint position_;
  QPixmap spiderImage_;
  QTimer* timer_;

  int lag_;
};

#endif  // SPIDER_H
