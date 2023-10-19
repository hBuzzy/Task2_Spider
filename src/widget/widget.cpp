#include "widget.h"

#include <QDateTime>
#include <QMouseEvent>
#include <QPainter>


Widget::Widget(QWidget *parent)
: QWidget(parent), timer_{this}, spider_{{10, 10}, "assets/spider.png"} {
    timer_.start(10);
    connect(&timer_, &QTimer::timeout, this, &Widget::MoveSpiderAutomatically);
}

Widget::~Widget() = default;

void Widget::MoveSpiderAutomatically() {
    switch (spider_.Move(QPoint(dx_, dy_) * 3, rect())) {
        case 1:
            dx_ = -dx_;
            break;
        case 2:
            dy_ = -dy_;
            break;
        default:
            repaint();
    }
}

void Widget::keyPressEvent(QKeyEvent* event) {
    QWidget::keyPressEvent(event);

    bool timer_active = timer_.isActive();
    switch (event->key()) {
        case Qt::Key_W:
            dirs_[0] = true;
            break;
        case Qt::Key_A:
            dirs_[1] = true;
            break;
        case Qt::Key_S:
            dirs_[2] = true;
            break;
        case Qt::Key_D:
            dirs_[3] = true;
            break;
        case Qt::Key_Shift:
            spider_.SetVelocity(3);
            break;
        case Qt::Key_Space:
            if (timer_active)
                timer_.stop();
            else
                timer_.start(10);
    }

    int dx = 0, dy = 0;
    if (dirs_[0])
        --dy;
    if (dirs_[1])
        --dx;
    if (dirs_[2])
        ++dy;
    if (dirs_[3])
        ++dx;

    spider_.SetVelocity(event->modifiers() == Qt::ShiftModifier ? 3 : 1);

    if (!(timer_active || spider_.Move(QPoint(dx, dy), rect())))
        repaint();
}

void Widget::keyReleaseEvent(QKeyEvent *event) {
    QWidget::keyReleaseEvent(event);

    switch (event->key()) {
        case Qt::Key_W:
            dirs_[0] = false;
            break;
        case Qt::Key_A:
            dirs_[1] = false;
            break;
        case Qt::Key_S:
            dirs_[2] = false;
            break;
        case Qt::Key_D:
            dirs_[3] = false;
            break;
        case Qt::Key_Shift:
            spider_.SetVelocity(1);
    }
}

void Widget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    spider_.Draw(&painter);
}
