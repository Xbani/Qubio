#ifndef QUGAME_H
#define QUGAME_H
#include <QGraphicsScene>
#include <QMap>

class QuEntity;
class QuGame : public QGraphicsScene
{
private:
    QMap<int,QuEntity*> entities;


public:
    QuGame();
    inline QMap<int,QuEntity*> getEntities() const {return entities;};
    void newMapFromJson(QJsonObject* JsonMap);
    void init();

    // QGraphicsScene interface
protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
};

#endif // QUGAME_H
