#ifndef WIDGET_H
#define WIDGET_H

#include <bitset>
#include <QWidget>
#include <QTimer>
#include "spider/spider.h"

struct KeyBindings {
    Qt::Key up = Qt::Key_W;
    Qt::Key left = Qt::Key_A;
    Qt::Key down = Qt::Key_S;
    Qt::Key right = Qt::Key_D;
    Qt::Key acceleration = Qt::Key_Shift;
    Qt::Key switchMode = Qt::Key_Space;
};

class Widget final : public QWidget {
    Q_OBJECT
public:
    explicit Widget(KeyBindings = {}, QWidget *parent = nullptr);
    ~Widget() final;
private slots:
    void MoveSpiderAutomatically();
protected:
    void paintEvent(QPaintEvent *event) final;
    void keyPressEvent(QKeyEvent *event) final;
    void keyReleaseEvent(QKeyEvent *event) final;
private:
    Spider spider_;
    KeyBindings keyBindings_;
    std::bitset<4> dirs_ = 0b0000;
    QTimer timer_;
    int dx_ = 1, dy_ = 1;
};

#endif
