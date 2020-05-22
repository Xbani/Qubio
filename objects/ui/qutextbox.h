#ifndef QUTEXTBOX_H
#define QUTEXTBOX_H

#include <objects/quobject.h>


/**
 * @brief The QuTextBox class
 * @details TextBox object : to set the character name.
 */
class QuTextBox : public QuObject
{
private:
    QImage sprite;
    QString text;
public:
    QuTextBox();
    QuTextBox(QString default_text);
    QString getText();

public:
    static const int MAX_TEXT_SIZE=22;


    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


    // QuObject interface
public:
    QJsonObject toJSON();
    void fromJSON(QJsonObject qJsonObject);


    // QGraphicsItem interface
protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // QUTEXTBOX_H
