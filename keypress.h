//Keypress.h
#ifndef KEYPRESS_WINDOW_H
#define KEYPRESS_WINDOW_H

#include  <QKeyEvent>

class KeyPress
{
    Q_OBJECT

    public:
        KeyPress();
        ~KeyPress();
        virtual void keyPressEvent(QKeyEvent *event);
    private slots:
        void closeHandler();
};



#endif //KEYPRESS_WINDOW_H
