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

private:
    void initMapBuilder();
    void clearScene();
    void resizeScene(QSize size);



public slots:
    void selectBlock(int block);
    void mapFromJson(QJsonObject* mapJson);
    QJsonObject* mapToJson();
    void createNewMap(QString mapName, QSize mapSize);

    // QGraphicsScene interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QSignalMapper *signalMapper;
    int blockSelected;
    QMenuBar *qMenuBar;
    QString mapName;
    QSize mapSize;
    bool mousePressed;
    bool mouseMoved;
};

#endif // QUMAPBUILDER_H
