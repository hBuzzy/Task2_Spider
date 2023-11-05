#include "web.h"

Web::Web(QPoint center, int radius, QPainter *painter, QObject *parent)
    : QObject{parent} {
  this->center_ = center;
  this->radius_ = radius;
  this->painter_ = painter;
  double secondParameter = 3.5;
  QVector<QPoint> points;
  points.append(QPoint(center.x(), center.y() - radius));
  points.append(QPoint(center.x() + radius - radius / secondParameter,
                       center.y() - radius + radius / secondParameter));
  points.append(QPoint(center.x() + radius, center.y()));
  points.append(QPoint(center.x() + radius - radius / secondParameter,
                       center.y() + radius - radius / secondParameter));
  points.append(QPoint(center.x(), center.y() + radius));
  points.append(QPoint(center.x() - radius + radius / secondParameter,
                       center.y() + radius - radius / secondParameter));
  points.append(QPoint(center.x() - radius, center.y()));
  points.append(QPoint(center.x() - radius + radius / secondParameter,
                       center.y() - radius + radius / secondParameter));

  for (int i = 0; i < points.size(); i++) {
    painter->drawLine(center.x(), center.y(), points[i].x(), points[i].y());
  }
  for (int i = 0; i < points.size() - 1; i++) {
    painter->drawLine(points[i].x(), points[i].y(), points[i + 1].x(),
                      points[i + 1].y());
  }
  painter->drawLine(points[0].x(), points[0].y(), points[7].x(), points[7].y());
  QPolygon polygon;
  int lineCount = 6;
  for (int j = 1; j < lineCount; j++) {
    double parameter;
    int endLine = lineCount - 1;
    int endLineWidth = 2;
    double linesWidth = 0.5;
    if (j == endLine) {
      parameter = j + endLineWidth;
    } else
      parameter = j + linesWidth;

    polygon
        << QPoint(center.x() - radius / parameter, center.y())
        << QPoint(center.x() + (-radius + radius / secondParameter) / parameter,
                  center.y() + (-radius + radius / secondParameter) / parameter)
        << QPoint(center.x(), center.y() - radius / parameter)
        << QPoint(center.x() + (radius - radius / secondParameter) / parameter,
                  center.y() + (-radius + radius / secondParameter) / parameter)
        << QPoint(center.x() + radius / parameter, center.y())
        << QPoint(center.x() + (radius - radius / secondParameter) / parameter,
                  center.y() + (radius - radius / secondParameter) / parameter)
        << QPoint(center.x(), center.y() + radius / parameter)
        << QPoint(center.x() + (-radius + radius / secondParameter) / parameter,
                  center.y() + (radius - radius / secondParameter) / parameter)
        << QPoint(center.x() - radius / parameter, center.y());

    painter->drawPolyline(polygon);
  }
}
