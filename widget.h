// widget.h
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "spider.h"

class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void moveSpider();
    void setSpeedSliderChanged(int value);
    void updateSpiderPositionChanged(const QPoint &position);
    void updateThreshold(int value);
    void updateLineWidth(int value);
    void setCursorStyle();

private:
    Spider *spider_;
    int speed_;
    QTimer *timer_;
    bool isdrawing_;
    QPoint center_;
    int lineWidth_;
    QColor lineColor_;
    bool isLeftKeyPressed_;
    bool isRightKeyPressed_;
    bool isUpKeyPressed_;
    bool isDownKeyPressed_;
    bool isLeftUpDiagonalPressed_;
    bool isRightUpDiagonalPressed_;
    bool isLeftDownDiagonalPressed_;
    bool isRightDownDiagonalPressed_;

};

#endif // WIDGET_H
