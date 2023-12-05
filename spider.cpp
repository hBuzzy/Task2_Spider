#include "spider.h"

Spider::Spider(QWidget *widget) : QWidget (widget), widget_(widget) {
    SetParameters();
}

void Spider::MoveSpider() {
    SetNextPoint();

    QPoint currentPos = spiderPos_;

    spiderPos_.setX(spiderPos_.x() + speed_ * spiderDirectionX_);

    if (spiderPos_.x() <= 0 || spiderPos_.x() >= widget_->width() - size_) {
        spiderPos_ = currentPos;
    }

    spiderPos_.setY(spiderPos_.y() + speed_ * spiderDirectionY_);

    if (spiderPos_.y() <= 0 || spiderPos_.y() >= widget_->height() - size_) {
        spiderPos_ = currentPos;
    }
}

void Spider::SetDirectionX(int directionX) {
    spiderDirectionX_ = directionX;
}

void Spider::SetDirectionY(int directionY) {
    spiderDirectionY_ = directionY;
}

int Spider::GetDirectionX() {
    return spiderDirectionX_;
}

int Spider::GetDirectionY() {
    return spiderDirectionY_;
}

void Spider::SetParameters() {
    speed_ = 5;
    size_ = 50;
    spiderDirectionX_ = 1;
    spiderDirectionY_ = 1;
    initialRotateAngle_ = 45;
    spiderImage_.load(":/sps");
    spiderImage_ = spiderImage_.scaled(size_, size_);

    int center = 2;
    int centerSpiderX_ = widget_->width() / center;
    int centerSpiderY_ = widget_->height() / center;
    spiderPos_ = QPoint(centerSpiderX_ - size_ / center, centerSpiderY_ - size_ / center);
}

void Spider::SetNextPoint() {
    int centerImage_ = 2;
    nextWayPoint_.setX(spiderPos_.x() + rotatedSpiderImage_.width() / centerImage_);
    nextWayPoint_.setY(spiderPos_.y() + rotatedSpiderImage_.height() / centerImage_);
    wayPoints_.append(nextWayPoint_);
}

QPixmap Spider::GetRotateImage() {
    return rotatedSpiderImage_ = spiderImage_.transformed(QTransform().rotate(GetRotateAngle()));
}

int Spider::GetRotateAngle() {
    if (spiderDirectionX_ > 0 && spiderDirectionY_ > 0) {
        return rotateAngles_[0];
    } else if (spiderDirectionX_ > 0 && spiderDirectionY_ < 0) {
        return rotateAngles_[1];
    } else if (spiderDirectionX_ < 0 && spiderDirectionY_ > 0) {
        return rotateAngles_[2];
    } else if (spiderDirectionX_ < 0 && spiderDirectionY_ < 0) {
        return rotateAngles_[3];
    } else if (spiderDirectionX_ < 0 && spiderDirectionY_ == 0) {
        return rotateAngles_[4];
    } else if (spiderDirectionX_ == 0 && spiderDirectionY_ < 0) {
        return rotateAngles_[5];
    } else if (spiderDirectionX_ > 0 && spiderDirectionY_ == 0) {
        return rotateAngles_[6];
    } else if (spiderDirectionX_ == 0 && spiderDirectionY_ > 0) {
        return rotateAngles_[7];
    }
    return 0;
}

QPoint Spider::GetSpiderPos() {
    return spiderPos_;
}

QVector<QPoint> Spider::GetWayPoint() {
    return wayPoints_;
}
