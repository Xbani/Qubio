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
    static const int MAX_TEXT_SIZE=60;
    static const int TEXT_FONT_SIZE=25;


    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;


    // QuObject interface
public:
    QJsonObject toJSON() override;
    void fromJSON(QJsonObject &qJsonObject) override;


    // QGraphicsItem interface
protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // QUTEXTBOX_H
