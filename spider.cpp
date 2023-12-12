#include "spider.h"

#include <QDir>
#include <QPainter>

Spider::Spider(QObject *parent, int width, int heigth) : QObject{parent} {
  QString currentPath = QDir::currentPath();
  QString parentPath = currentPath + "/spider5.png";

  pixmap_ = QPixmap(parentPath);

  width_ = width;
  height_ = heigth;
}

void Spider::DrawSpider(QPainter *painter, QPoint position) {
  int halthDevider = 2;

  QRect rect(position.x() - width_ / halthDevider,
             position.y() - height_ / halthDevider, width_, height_);
  painter->drawPixmap(rect, pixmap_);
}

void Spider::DrawTrack(QPainter *painter) {
  int trackCount = track_.count();
  int offset = 1;

  if (trackCount > 1) {
    for (int i = 1; i < trackCount; i++) {
      painter->drawLine(track_[i - offset], track_[i]);
    }
  }
}

void Spider::UpdateTrack(QPoint position) { track_.append(position); }
