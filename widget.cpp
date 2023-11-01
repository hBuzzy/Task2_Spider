#include "widget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QPoint>
#include <QPainter>
#include <QVector>
#include <QLabel>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QPushButton* startButton = new QPushButton("Начать");
    QPushButton* stopButton = new QPushButton("Остановить");
    QPushButton* speedButton = new QPushButton("Ускорить");
    QPushButton* slowDownButton = new QPushButton("Замедлить");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(&spiderWeb_);
    layout->addWidget(startButton);
    layout->addWidget(stopButton);
    layout->addWidget(speedButton);
    layout->addWidget(slowDownButton);

    connect(startButton, &QPushButton::clicked, &spider_, &Spider::Start);
    connect(stopButton, &QPushButton::clicked, &spider_, &Spider::Stop);
    connect(speedButton, &QPushButton::clicked, &spider_, &Spider::IncreaseSpeed);
    connect(slowDownButton, &QPushButton::clicked, &spider_, &Spider::DecreaseSpeed);

    connect(&spider_, &Spider::SpiderMoved, this, &Widget::AddPointToWeb);

}

void Widget::paintEvent(QPaintEvent *) {
    QPixmap spiderPixmap(":/images/spider.png");
    spiderPixmap = spiderPixmap.scaled(50, 50, Qt::KeepAspectRatio);
    QPainter painter(this);
    painter.setPen(QPen(Qt::black,4));

    for (const QPoint &point : webPoints) {
        painter.drawPoint(point);
    }
    painter.drawPixmap(spider_.GetPosition(), spiderPixmap);
}

void Widget::AddPointToWeb(const QPoint &position) {
    webPoints.append(position);
    update();
}

Widget::~Widget(){}
