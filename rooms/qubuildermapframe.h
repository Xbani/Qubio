#ifndef QUBUILDERMAPFRAME_H
#define QUBUILDERMAPFRAME_H

#include <QGraphicsView>
#include <QMainWindow>
#include <QSignalMapper>

class QuMapBuilder;
namespace Ui {
class QuBuilderMapFrame;
}

class QuBuilderMapFrame : public QMainWindow
{
    Q_OBJECT

public:
    explicit QuBuilderMapFrame(QGraphicsView *view,QWidget *parent = nullptr);
    ~QuBuilderMapFrame();

private:
    void init();


private:
    Ui::QuBuilderMapFrame *ui;
    QSignalMapper *signalMapper;
    QuMapBuilder *mapBuilder;

private slots:
    void openMap();
    void newMap();
    void save();
    void saveUnder();
    void rename();
};

#endif // QUBUILDERMAPFRAME_H
