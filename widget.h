// widget.h
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "spider.h"

class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void moveSpider();
    void speedSliderChanged(int value);
    void spiderPositionChanged(const QPoint &position);

private:
    Spider *_spider;
    int _speed;
    QTimer *_timer;

};

#endif // WIDGET_H
