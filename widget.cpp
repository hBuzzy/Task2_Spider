#include "widget.h"
#include "spider.h"

#include <QPainter>
#include <QKeyEvent>

Widget::Widget(QWidget *parent) : QWidget(parent) {
    spider_ = new Spider(this);
    timer_ = new QTimer();
    connect(timer_, &QTimer::timeout, this, &Widget::TikTime);
    timer_->start(500);
}

Widget::~Widget() {}

void Widget::paintEvent(QPaintEvent *){
    QPainter painter;
    painter.begin(this);

    const int sizePoxmap = 10;
    QPixmap pixmap(sizePoxmap, sizePoxmap);
    pixmap.fill(Qt::black);

    painter.drawPixmap(spider_->GetCurrentPosition().x() - sizePoxmap/2, spider_->GetCurrentPosition().y() - sizePoxmap/2, pixmap);
    QList currentLines = spider_->GetWebLines();

    for (int i = 0; i < currentLines.size(); i++) {
        painter.drawLine(currentLines[i]);
    }
    painter.end();
}

void Widget::keyPressEvent(QKeyEvent *event) {
    const int linkage = 0;
    const int step = 10;
    if (event->key() == Qt::Key_Up) {
        spider_->SetVelocity(QPoint(linkage,-step));
    }
    if (event->key() == Qt::Key_Down) {
        spider_->SetVelocity(QPoint(linkage, step));
    }
    if (event->key() == Qt::Key_Left) {
        spider_->SetVelocity(QPoint(-step, linkage));
    }
    if (event->key() == Qt::Key_Right) {
        spider_->SetVelocity(QPoint(step, linkage));
    }
    this->update();
}

void Widget::TikTime()
{
    spider_->SetWeb(Widget::rect());
    this->update();
}
