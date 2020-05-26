#ifndef QUMAPBUILDER_H
#define QUMAPBUILDER_H

#include <QGraphicsScene>





class QuMapBuilder : public QGraphicsScene
{
public:
    QuMapBuilder(qreal x, qreal y, qreal width, qreal height, QObject * parent = nullptr);

private:
    void init();
};

#endif // QUMAPBUILDER_H
