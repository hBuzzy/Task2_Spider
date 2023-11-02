#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    spider_ = new Spider(this->width(), this->height());
    timer_ = new QTimer();
    connect(timer_, &QTimer::timeout, spider_, &Spider::addPoint);
    connect(timer_, &QTimer::timeout, this, &MainWindow::update);
    timer_->start(100);

}

void MainWindow::update() {
    repaint();
}

void MainWindow::paintEvent(QPaintEvent *event) {
    spider_->paint(this);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    spider_->updateState(event, true);
    if (!event->isAutoRepeat()) {
        spider_->updateState(event, false);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    spider_->updateState(event, false);
}

MainWindow::~MainWindow() {
    delete ui_;
    delete timer_;
}

