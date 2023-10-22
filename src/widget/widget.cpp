#include "widget.h"

#include <QDateTime>
#include <QMouseEvent>
#include <QPainter>


Widget::Widget(KeyBindings keyBindings, QWidget *parent):
QWidget(parent), spider_{{10, 10}, "assets/spider.png", 1, 3},
keyBindings_(keyBindings), timer_{this} {
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
    auto key = event->key();
    if (key == keyBindings_.up)
        dirs_[0] = true;
    else if (key == keyBindings_.left)
        dirs_[1] = true;
    else if (key == keyBindings_.down)
        dirs_[2] = true;
    else if (key == keyBindings_.right)
        dirs_[3] = true;
    else if (key == keyBindings_.acceleration)
        spider_.SetVelocity(spider_.GetVelocityFast());
    else if (key == keyBindings_.switchMode) {
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

    if (!(timer_active || spider_.Move(QPoint(dx, dy), rect())))
        repaint();
}

void Widget::keyReleaseEvent(QKeyEvent *event) {
    QWidget::keyReleaseEvent(event);

    auto key = event->key();
    if (key == keyBindings_.up)
        dirs_[0] = false;
    else if (key == keyBindings_.left)
        dirs_[1] = false;
    else if (key == keyBindings_.down)
        dirs_[2] = false;
    else if (key == keyBindings_.right)
        dirs_[3] = false;
    else if (key == keyBindings_.acceleration)
        spider_.SetVelocity(spider_.GetVelocitySlow());
}

void Widget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    spider_.Draw(&painter);
}
