#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Spider;

class Widget : public QWidget {
  Q_OBJECT

 public:
  Widget(QWidget *parent = nullptr);
  ~Widget();

  protected:
  void paintEvent(QPaintEvent*) override;
  void keyPressEvent(QKeyEvent *event) override;

  private:
  Spider *spider;

};

#endif  // WIDGET_H
