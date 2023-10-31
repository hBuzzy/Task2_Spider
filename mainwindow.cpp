#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    isDown_ = false;
    isUp_ = false;
    isLeft_ = false;
    isRight_ = false;

    x_ = this->width()/2;
    y_ = this->height()/2;

    points_ = new QVector<QPoint>();

    timer_ = new QTimer();
    connect(timer_, SIGNAL(timeout()), this, SLOT(addPoint()));
    timer_->start(100);

}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap spider = QPixmap(":/img/spider.png");

    QPen pen = QPen(Qt::black);
    pen.setWidth(kStep);
    painter.setPen(pen);

    for (QPoint point : *points_) {
        painter.drawPoint(point);
    }

    painter.rotate(0);
    painter.drawPixmap(x_ - (kStep * 20) / 2, y_ + 0, kStep * 20, kStep * 20, spider);

}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    updateState(event, true);
    if (!event->isAutoRepeat()) {
        updateState(event, false);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    updateState(event, false);
}

void MainWindow::addPoint() {
    x_ += isRight_ * kStep + isLeft_ * -1 * kStep;
    y_ += isDown_ * kStep + isUp_ * -1 * kStep;

    points_->push_back({ x_, y_ });
    repaint();
}

void MainWindow::updateState(QKeyEvent *event, bool state) {
    switch (event->key()) {
        case Qt::Key_Right:
            isRight_ = state;
            break;
        case Qt::Key_Left:
            isLeft_ = state;
            break;
        case Qt::Key_Down:
            isDown_ = state;
            break;
        case Qt::Key_Up:
            isUp_ = state;
            break;
    }
}

MainWindow::~MainWindow() {
    delete ui_;
    delete points_;
    delete timer_;
}

