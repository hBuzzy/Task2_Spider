#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent) { ParametersSpider(); }
Widget::~Widget() {}

void Widget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    QPen pointPen = painter.pen();
    pointPen.setWidth(SizePoint_);
    painter.setPen(pointPen);
    for (QPoint point : points_) {
        painter.drawPoint(point);
    }

    rotatedSpiderImage_ = SpiderImage_.transformed(QTransform().rotate(GetRotateAngle()));
    painter.drawPixmap(SpiderPoint_, rotatedSpiderImage_);
}
void Widget::MoveSpider() {
    VecPointLine();

    SpiderPoint_.setX(SpiderPoint_.x() + SpiderSpeed_ * SpiderDirX_);
    if (SpiderPoint_.x() <= 0 || SpiderPoint_.x() >= width() - SizeSpider_) {
        SpiderDirX_ *= -1;
        AngleRotate_ *= -1;
    }

    SpiderPoint_.setY(SpiderPoint_.y() + SpiderSpeed_ * SpiderDirY_);
    if (SpiderPoint_.y() <= 0 || SpiderPoint_.y() >= height() - SizeSpider_) {
        SpiderDirY_ *= -1;
    }
    update();
}
void Widget::ParametersSpider() {
    SizePoint_ = 3;
    SpiderSpeed_ = 5;
    SizeSpider_ = 50;
    SpiderDirX_ = 1;
    SpiderDirY_ = 1;
    AngleRotate_ = 45;
    NumbTimer = 50;
    int CenterSpiderX_ = width() / 2;
    int CenterSpiderY_ = height() / 2;
    SpiderPoint_ = QPoint(CenterSpiderX_ - SizeSpider_ / 2, CenterSpiderY_ - SizeSpider_ / 2);
    SpiderImage_.load(":/sps");
    SpiderImage_ = SpiderImage_.scaled(SizeSpider_, SizeSpider_);

    SpiderTimer_ = new QTimer(this);
    SpiderTimer_->setInterval(NumbTimer);
    connect(SpiderTimer_, &QTimer::timeout, this, &Widget::MoveSpider);
    SpiderTimer_->start();
}
void Widget::VecPointLine() {
    int CenterImage_ = 2;
    NewPoint_.setX(SpiderPoint_.x() + rotatedSpiderImage_.width() / CenterImage_);
    NewPoint_.setY(SpiderPoint_.y() + rotatedSpiderImage_.height() / CenterImage_);
    points_.append(NewPoint_);
    update();
}
int Widget::GetRotateAngle() {
    if (SpiderDirX_ > 0 && SpiderDirY_ > 0) {
        return 135;
    } else if (SpiderDirX_ > 0 && SpiderDirY_ < 0) {
        return 45;
    } else if (SpiderDirX_ < 0 && SpiderDirY_ > 0) {
        return -135;
    } else if (SpiderDirX_ < 0 && SpiderDirY_ < 0) {
        return -45;
    }
    return 0;
}
