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
  void SetWeb(const QRect &windowRect);
  void SetSpeedVector(const QPoint &speedAddValue);

  private:
  QList<QLine> webLines;
  QPoint currentPosition;
  QPoint speedVector;
};

#endif  // SPIDER_H
