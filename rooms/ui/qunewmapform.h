#ifndef NEWMAPFORM_H
#define NEWMAPFORM_H

#include <QDialog>

namespace Ui {
class QuNewMapForm;
}

class QuNewMapForm : public QDialog
{
    Q_OBJECT

public:
    explicit QuNewMapForm(QWidget *parent = nullptr);
    ~QuNewMapForm();
    QString getMapName();
    QSize getMapSize();

private:
    Ui::QuNewMapForm *ui;
};

#endif // NEWMAPFORM_H
