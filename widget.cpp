// widget.cpp
#include "widget.h"
#include <QPainter>
#include <QSlider>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent) : QWidget(parent), _speed(5) {
    _spider = new Spider(this);
    connect(_spider, &Spider::positionChanged, this, &Widget::spiderPositionChanged);

    _timer = new QTimer(this);
    connect(_timer, &QTimer::timeout, this, &Widget::moveSpider);
    _timer->start(100);

    QSlider *speedSlider = new QSlider(Qt::Horizontal);
    speedSlider->setMinimum(1);
    speedSlider->setMaximum(10);
    speedSlider->setValue(5);
    connect(speedSlider, &QSlider::valueChanged, this, &Widget::speedSliderChanged);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(speedSlider);
    setLayout(layout);

    _spider->startMoving();
}

Widget::~Widget() {
    delete _spider;
}

void Widget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(_spider->getPosition(), _spider->getSpiderImage());

    // Рисуем линию паутины
    painter.setPen(QPen(Qt::black, 2));  // Выбираем черный цвет и толщину линии
    for (const QPoint &point : _spider->getPath()) {
        painter.drawPoint(point);
    }
}

void Widget::spiderPositionChanged(const QPoint &position) {
    update();
}

void Widget::speedSliderChanged(int value) {
    _speed = value;
    _spider->setSpeed(_speed);
}

void Widget::moveSpider() {
    _spider->moveSpider();
}
