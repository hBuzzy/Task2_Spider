#ifndef WIDGET_H
#define WIDGET_H

#include <bitset>
#include <QWidget>
#include <QTimer>
#include "spider/spider.h"

class Widget : public QWidget {
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
private slots:
    void MoveSpiderAutomatically();
protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
private:
    Spider spider_;
    std::bitset<4> dirs_ = 0b0000;
    QTimer timer_;
    int dx_ = 1, dy_ = 1;
};

#endif
