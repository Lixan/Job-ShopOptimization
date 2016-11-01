#ifndef GRAPHEWINDOW_H
#define GRAPHEWINDOW_H

#include <QPaintEvent>
#include <QDialog>
#include <QWidget>
#include "Bierwirth.h"
#include "Data.h"

class GrapheWindow : public QWidget
{
    Q_OBJECT
    Data *data;
    Bierwirth *bierwirth;

public:
    GrapheWindow(Data *d, Bierwirth *b, QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    void draw(QRect &rect);

signals:

public slots:
};

#endif // GRAPHEWINDOW_H