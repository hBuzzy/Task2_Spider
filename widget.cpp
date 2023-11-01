#include "widget.h"
#include "spider.h"

#include <QPainter>
#include <QKeyEvent>

Widget::Widget(QWidget *parent) : QWidget(parent) {
    spider_ = new Spider(this);
    timer_ = new QTimer();
    connect(timer_, &QTimer::timeout, this, &Widget::tikTime_);
    timer_->start(500);
}

Widget::~Widget() {}

void Widget::paintEvent(QPaintEvent *){
    QPainter painter;
    painter.begin(this);
    QPixmap pixmap(10, 10);
    pixmap.fill(Qt::black);
    painter.drawPixmap(spider_->GetCurrentPosition().x() - 5, spider_->GetCurrentPosition().y() - 5, pixmap);
    QList currentLines = spider_->GetWebLines();

    for (int i = 0; i < currentLines.size(); i++) {
        painter.drawLine(currentLines[i]);
    }
    painter.end();
}

void Widget::keyPressEvent(QKeyEvent *event) {
    const int linkage = 0;
    const int step = 10;
    if(event->key() == Qt::Key_Up){
        spider_->SetSpeedVector(QPoint(linkage,-step));
    }
    if(event->key() == Qt::Key_Down){
        spider_->SetSpeedVector(QPoint(linkage, step));
    }
    if(event->key() == Qt::Key_Left){
        spider_->SetSpeedVector(QPoint(-step, linkage));
    }
    if(event->key() == Qt::Key_Right){
        spider_->SetSpeedVector(QPoint(step, linkage));
    }
    this->update();
}

void Widget::tikTime_()
{
    spider_->SetWeb(Widget::rect());
    this->update();
}
