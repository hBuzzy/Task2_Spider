#include "spider.h"

#include <math.h>

#include <QDebug>
#include <QDir>

Spider::Spider(int lag, QPoint position, QObject *parent) : QObject{parent} {
  lag_ = lag;

  QString currentPath = QDir::currentPath();
  QDir parentDir(currentPath);
  parentDir.cdUp();
  QString parentPath = parentDir.absolutePath();

  spiderImage_ = QPixmap(parentPath + "Task2_Spider-katnag" + "/rac.png");

  position_ = position;
}

QList<QPoint> Spider::GetWeb() { return web_; }

QPoint Spider::GetPosition() { return position_; }

QPoint Spider::ConstrainPointToBounds(QPoint point, int widgetWidth,
                                      int widgetHeight) {
  int spiderHeight = spiderImage_.height();
  int spiderWidth = spiderImage_.width();

  int x = point.x();
  int y = point.y();

  if (x < 0) {
    x = 0;
  }
  if (y + spiderWidth > widgetWidth) {
    x = widgetWidth - spiderWidth;
  }
  if (y < 0) {
    y = 0;
  }
  if (y + spiderHeight > widgetHeight) {
    y = widgetHeight - spiderHeight;
  }

  return (QPoint(x, y));
}

QPoint Spider::CalculateNewPosition(int widgetWidth, int widgetHeight) {
  static double t = 0.0;
  double step = 0.005;
  const int xAmplitude = 100;
  const int yAmplitude = 85;
  const int halfDelimeter = 2;

  double x = sin(t) * (exp(cos(t)) - 2 * cos(4 * t) - pow(sin(t / 12), 5));
  double y = cos(t) * (exp(cos(t)) - 2 * cos(4 * t) - pow(sin(t / 12), 5));

  int centerX = static_cast<int>(widgetWidth / halfDelimeter + xAmplitude * x);
  int centerY = static_cast<int>(widgetHeight / halfDelimeter + yAmplitude * y);

  int spiderHeight = spiderImage_.height();
  int spiderWidth = spiderImage_.width();

  int spiderCenterX = centerX - spiderWidth / halfDelimeter;
  int spiderCenterY = centerY - spiderHeight / halfDelimeter;

  t += step;

  return QPoint(spiderCenterX, spiderCenterY);
}

QPixmap Spider::GetImage() { return spiderImage_; }

void Spider::Move(int widgetWidth, int widgetHeight) {
  position_ =
      ConstrainPointToBounds(CalculateNewPosition(widgetWidth, widgetHeight),
                             widgetWidth, widgetHeight);
  web_.append(QPoint(position_.x(), position_.y() + spiderImage_.height()));
}

void Spider::SetLag(int lag) { lag_ = lag; }

int Spider::GetLag() { return lag_; }
