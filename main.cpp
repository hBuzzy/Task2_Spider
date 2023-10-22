#include <QApplication>
#include "widget/widget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Widget w({
        Qt::Key_W,
        Qt::Key_A,
        Qt::Key_S,
        Qt::Key_D,
        Qt::Key_Shift,
        Qt::Key_Space
    });
    w.show();
    return QApplication::exec();
}
