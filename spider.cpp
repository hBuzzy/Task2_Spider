#include "spider.h"

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

void Spider::Move(int widgetWidth, int widgetHeight) {
  static double t = 0.0;

  double x = sin(t) * (exp(cos(t)) - 2 * cos(4 * t) - pow(sin(t / 12), 5));
  double y = cos(t) * (exp(cos(t)) - 2 * cos(4 * t) - pow(sin(t / 12), 5));

  int centerX = static_cast<int>(widgetWidth / 2 + 100 * x);
  int centerY = static_cast<int>(widgetHeight / 2 + 100 * y);

  int spiderHeight = spiderImage_.height();
  int spiderWidth = spiderImage_.width();

  int spiderCenterX = centerX - spiderWidth / 2;
  int spiderCenterY = centerY - spiderHeight / 2;

  if (spiderCenterX < 0) {
    spiderCenterX = 0;
  }
  if (spiderCenterX + spiderWidth > widgetWidth) {
    spiderCenterX = widgetWidth - spiderWidth;
  }
  if (spiderCenterY < 0) {
    spiderCenterY = 0;
  }
  if (spiderCenterY + spiderHeight > widgetHeight) {
    spiderCenterY = widgetHeight - spiderHeight;
  }

  web_.append(QPoint(spiderCenterX, spiderCenterY + spiderHeight));

  position_ = QPoint(spiderCenterX, spiderCenterY);

  t += 0.005;
}

QPoint Spider::GetPosition() { return position_; }

QPixmap Spider::GetImage() { return spiderImage_; }

void Spider::SetLag(int lag) { lag_ = lag; }

int Spider::GetLag() { return lag_; }

void Spider::MoveSpider() { emit SpiderMoved(position_); }
