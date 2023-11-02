#ifndef SPIDER_H
#define SPIDER_H

#include <QObject>
#include <QKeyEvent>
#include <QPixmap>
#include <QPainter>
#include <QWidget>

class Spider : public QObject
{
    Q_OBJECT
public:
    Spider(int maxX, int maxY);
    ~Spider();
    void updateState(QKeyEvent *event, bool state);
    void paint(QWidget *ctx);

public slots:
    void addPoint();

private:
    const int kStep = 2;
    int isDown_;
    int isUp_;
    int isLeft_;
    int isRight_;
    int x_;
    int y_;
    QVector<QPoint> *points_;
};

#endif // SPIDER_H
