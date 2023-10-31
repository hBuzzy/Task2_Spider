#include "widget.h"
#include "spider.h"

#include <QPainter>
#include <QKeyEvent>

Widget::Widget(QWidget *parent) : QWidget(parent) {
    spider = new Spider(this);
}

Widget::~Widget() {}

void Widget::paintEvent(QPaintEvent *){

    QPainter painter;
    painter.begin(this);
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
    //TODO заментиь на тики
    if(event->key() == Qt::Key_0){
        spider->SetWeb(QWidget::rect());
    }
    this->update();
}
