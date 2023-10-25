#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent) {
  spider_ = new Spider(10, QPoint(0, 0), this);
  drawTimer_ = new QTimer(this);

  connect(drawTimer_, &QTimer::timeout, this, &Widget::drawSpider);

  drawTimer_->start(spider_->GetLag());
}

Widget::~Widget() {}

void Widget::resizeEvent(QResizeEvent *event) {
  Q_UNUSED(event);

  windowRect_ = rect();
}

void Widget::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event)

  QPainter painter(this);

  QList<QPoint> web = spider_->GetWeb();
  for (const QPoint &point : web) {
    painter.drawPoint(point);
  }

  painter.drawPixmap(spider_->GetPosition().x(), spider_->GetPosition().y(),
                     spider_->GetImage());
}

void Widget::drawSpider() {
  spider_->Move(windowRect_.width(), windowRect_.height());

  update();
}

void Widget::keyPressEvent(QKeyEvent *event) {
  int lagChange = 1;
  int currentLag = spider_->GetLag();

  if (event->key() == Qt::Key_Right) {
    if (currentLag - lagChange >= 0) {
      spider_->SetLag(currentLag - lagChange);
    }
  } else if (event->key() == Qt::Key_Left) {
    spider_->SetLag(currentLag + lagChange);
  }

  qDebug() << spider_->GetLag();
  updateTimer(spider_->GetLag());
}

void Widget::updateTimer(int lag) {
  drawTimer_->stop();
  delete drawTimer_;

  drawTimer_ = new QTimer(this);
  connect(drawTimer_, &QTimer::timeout, this, &Widget::drawSpider);
  drawTimer_->start(lag);
}
