#include "widget.h"
#include <QPoint>
#include <QStyle>

Widget::Widget(QWidget *parent) : QWidget(parent) {}

Widget::~Widget() {}

void Widget::paintEvent(QPaintEvent *event) {
    QPixmap spiderPixmap(":/resources/Spider.png");
    QPainter painter(this);
    QPen pen(Qt::white, 3);
    painter.setPen(pen);
    QList<QPoint> currentLines = spider_.getWebPoints();
    for (int i = 1; i < currentLines.size(); i++) {
            painter.drawLine(currentLines[i - 1], currentLines[i]);
        }
    painter.drawPixmap(spider_.getPosition(), spiderPixmap);
}
void Widget::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_S) {
        spider_.moveSpider(0, spider_.getSpiderStep().y());
        repaint();
      }
    if (event->key() == Qt::Key_W) {
        spider_.moveSpider(0, - spider_.getSpiderStep().y());
        repaint();
      }
    if (event->key() == Qt::Key_D) {
        spider_.moveSpider(spider_.getSpiderStep().x(), 0);
        repaint();
      }
    if (event->key() == Qt::Key_A) {
        spider_.moveSpider( - spider_.getSpiderStep().x(), 0);
        repaint();
      }
    if (event->key() == Qt::Key_Q) {
        spider_.speedDown();
      }
    if (event->key() == Qt::Key_E) {
        spider_.speedUp();
      }
}
