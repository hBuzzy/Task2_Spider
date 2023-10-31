#include "spider.h"

Spider::Spider(QObject *parent) : QObject{parent} {
    currentPosition = QPoint(100,100);
    speedVector = QPoint(0,0);
}

QList<QLine> Spider::GetWebLines() { return webLines; }

void Spider::SetWeb(const QRect &windowRect) {
    float pi = 3.14;
    webLines.append(QLine(currentPosition, QPoint(currentPosition.x() + speedVector.x(), currentPosition.y() + speedVector.y())));
    currentPosition = QPoint(currentPosition.x() + speedVector.x(), currentPosition.y() + speedVector.y());
    if (currentPosition.x() > windowRect.right()){
        currentPosition.setX() = windowRect.right();
    }
//    if (currentPosition.x() < 0){
//        currentPosition.x() = 0;
//    }
//    if (currentPosition.y() > windowRect.bootom()){
//        currentPosition.y() = windowRect.bootom();
//    }
//    if (currentPosition.y() < 0){
//        currentPosition.y() = 0;
//    }
}

void Spider::SetSpeedVector(const QPoint &speedAddValue)
{
    speedVector = QPoint(speedVector.x() + speedAddValue.x(), speedVector.y() + speedAddValue.y());
}
