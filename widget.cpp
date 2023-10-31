#include "widget.h"
#include "spider.h"

#include <QPainter>
#include <QKeyEvent>

Widget::Widget(QWidget *parent) : QWidget(parent) {
    spider = new Spider(this);
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Widget::tikTime);
    timer->start(500);
}

Widget::~Widget() {}

void Widget::paintEvent(QPaintEvent *){

    QPainter painter;
    painter.begin(this);

    //не хотит паук появляться... пытаюсь разобраться, но пока так
    QRectF target(10.0, 20.0, 80.0, 60.0);
    QRectF source(0.0, 0.0, 70.0, 40.0);
    QPixmap pixmap(":pauk.png");
    painter.drawPixmap(target, pixmap, source);

    QList currentLines = spider->GetWebLines();
    for (int i = 0; i < currentLines.size(); i++) {
        painter.drawLine(currentLines[i]);
    }
    painter.end();
}
void Widget::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Up){
        spider->SetSpeedVector(QPoint(0,-10));
    }
    if(event->key() == Qt::Key_Down){
        spider->SetSpeedVector(QPoint(0, 10));
    }
    if(event->key() == Qt::Key_Left){
        spider->SetSpeedVector(QPoint(-10, 0));
    }
    if(event->key() == Qt::Key_Right){
        spider->SetSpeedVector(QPoint(10, 0));
    }
    this->update();
}
void Widget::tikTime()
{
    spider->SetWeb(Widget::rect());
    this->update();
}
