#ifndef SPIDER_H
#define SPIDER_H

#include <QObject>
#include <QPoint>
#include <QLine>
#include <QRect>

class Spider : public QObject {
  Q_OBJECT
 public:
  explicit Spider(QObject *parent = nullptr);

  QList<QLine> GetWebLines();
  QPoint GetCurrentPosition();
  void SetWeb(const QRect &windowRect);
  void SetVelocity(const QPoint &speedAddValue);

  private:
  QList<QLine> webLines_;
  QPoint currentPosition_;
  QPoint velocity_;
};

#endif  // SPIDER_H
