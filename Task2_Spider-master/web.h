#ifndef WEB_H
#define WEB_H
#include <QPainter>
class Web : public QObject {
  Q_OBJECT
 public:
  explicit Web(QPoint, int, QPainter *, QObject *parent = nullptr);

 private:
  QPainter *painter_;
  QPoint center_;
  int radius_;
  QVector<QPoint> webWayPoints_;
};

#endif  // WEB_H
