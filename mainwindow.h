#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QPainter>
#include <QVector>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    ~MainWindow();

public slots:
    void addPoint();

private:
    void updateState(QKeyEvent *event, bool state);

private:
    const int kStep = 2;
    Ui::MainWindow *ui_;
    int isDown_;
    int isUp_;
    int isLeft_;
    int isRight_;
    int x_;
    int y_;
    QVector<QPoint> *points_;
    QTimer *timer_;
};
#endif // MAINWINDOW_H
