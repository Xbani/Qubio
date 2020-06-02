#ifndef KEYENTERRECEIVER_H
#define KEYENTERRECEIVER_H

#include <QObject>

class KeyEnterReceiver : public QObject
{
    Q_OBJECT
public:
    explicit KeyEnterReceiver(QObject *parent = nullptr);

protected:
    bool eventFilter(QObject* obj, QEvent* event);

signals:

};

#endif // KEYENTERRECEIVER_H
