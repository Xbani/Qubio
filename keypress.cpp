//Keypress.cpp
#include "Keypress.h"

KeypressWindow::KeypressWindow(QMainWindow *parent) :
        QMainWindow(parent)
{
    setupUi(this);
    connect(actionClose,SIGNAL(triggered()),this,SLOT(closeHandler()));
}

KeypressWindow::~KeypressWindow()
{
}

void KeypressWindow::closeHandler()
{
    close();
}

void KeypressWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_A:
        label->setText("A pressed");
        break;
    case Qt::Key_B:
        label->setText("B pressed");
        break;
    default:
        label->setText("Something else pressed");
        break;
    }
}
