#ifndef SPIDER_H
#define SPIDER_H

#include <QObject>
#include <QPoint>
#include <QTimer>

class Spider : public QObject {
    Q_OBJECT
public:
    Spider(QObject *parent = nullptr);
    void Start();
    void Stop();
    void IncreaseSpeed();
    void DecreaseSpeed();
    QPoint GetPosition() const;

signals:
    void SpiderMoved(const QPoint &position);

private slots:
    void Move();

private:
    QTimer timer;
    QPoint position;
    int speed;
    QPoint trajectory;
};

#endif // SPIDER_H
