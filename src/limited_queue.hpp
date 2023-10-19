#ifndef LIMITED_QUEUE_H
#define LIMITED_QUEUE_H

#include <QQueue>

template <typename T, std::size_t n>
class LimitedQueue : public QQueue<T> {
    static constexpr std::size_t maxSize_ = n;
public:
    inline void enqueue(const T &t) {
        if (QList<T>::length() == n)
            QList<T>::takeFirst();
        QList<T>::append(t);
    };
    inline T dequeue() {
        return QList<T>::takeFirst();
    };
};

#endif
