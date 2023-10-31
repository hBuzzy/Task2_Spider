#include "spider.h"

Spider::Spider(QObject *parent) : QObject{parent} {
    currentPosition = QPoint(100,100);
    speedVector = QPoint(0,0);
}

QList<QLine> Spider::GetWebLines() { return webLines; }

void Spider::SetWeb(const QRect &windowRect) {
    float pi = 3.14;
    int xMoving = currentPosition.x() + speedVector.x();
    int yMoving = currentPosition.y() + speedVector.y();
    if (xMoving > windowRect.width()){
        xMoving = windowRect.width();
        speedVector.setX(-speedVector.x());
    }
    if (xMoving < 0){
        xMoving = 0;
        speedVector.setX(-speedVector.x());
    }
    if (yMoving > windowRect.height()){
        yMoving = windowRect.height();
        speedVector.setY(-speedVector.y());
    }
    if (yMoving < 0){
        yMoving = 0;
        speedVector.setY(-speedVector.y());
    }

    webLines.append(QLine(currentPosition, QPoint(xMoving, yMoving)));
    currentPosition = QPoint(xMoving, yMoving);
}
void Spider::SetSpeedVector(const QPoint &speedAddValue)
{
    speedVector = QPoint(speedVector.x() + speedAddValue.x(), speedVector.y() + speedAddValue.y());
}
