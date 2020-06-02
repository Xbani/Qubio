#ifndef QUMAPBUILDER_H
#define QUMAPBUILDER_H

#include <QGraphicsScene>
#include <QMenuBar>
#include <QSignalMapper>

class QuMapBuilder : public QGraphicsScene
{
    Q_OBJECT
public:
    QuMapBuilder(qreal x, qreal y, qreal width, qreal height, QObject * parent = nullptr);
    void initMapBuilder();

private:
    QSignalMapper *signalMapper;
    int blockSelected;
    QMenuBar *qMenuBar;



public slots:
    void selectBlock(int block);

    // QGraphicsScene interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    bool mousePressed;
    bool mouseMoved;
};

#endif // QUMAPBUILDER_H
