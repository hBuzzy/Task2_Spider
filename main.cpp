#include <QApplication>

#include "spider.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Spider s;
  s.show();
  return a.exec();
}
