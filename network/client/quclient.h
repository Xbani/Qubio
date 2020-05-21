#ifndef QUCLIENT_H
#define QUCLIENT_H

#include <QObject>
#include <QThread>

class QuClient : public QThread
{
    Q_OBJECT

public:
    explicit QuClient(QObject *parent = nullptr);

private:
    void run() override;
signals:

};

#endif // QUCLIENT_H
