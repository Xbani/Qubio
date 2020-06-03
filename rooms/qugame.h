#ifndef QUGAME_H
#define QUGAME_H
#include <QGraphicsScene>
#include <QMap>

class QuEntity;
class QuPlayerInfo;
class QuGameEngine;
class QuGame : public QGraphicsScene
{
private:
    QMap<int,QuEntity*> entities;
    QuGameEngine * quGameEngine;

public:
    QuGame(qreal x, qreal y, qreal width, qreal height, QObject *parent);
    inline QMap<int,QuEntity*> getEntities() const {return entities;};
    void newMapFromJson(QJsonObject* JsonMap);
    void init();
    void createPlayers(QMap<int,QuPlayerInfo *>);



    // QGraphicsScene interface
protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
};

#endif // QUGAME_H
