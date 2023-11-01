#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPoint>
#include <QVector>

#include "spider.h"
#include "spiderweb.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Spider spider_;
    SpiderWeb spiderWeb_;
    QVector<QPoint> webPoints;


public slots:
    void AddPointToWeb(const QPoint &position);
};

#endif // WIDGET_H
