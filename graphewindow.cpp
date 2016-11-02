#include "graphewindow.h"
#include <QPaintEvent>
#include <QPainter>
#include <QRectF>
#include <QLabel>
#include <QLineF>


GrapheWindow::GrapheWindow(Data *d, Bierwirth *b, QWidget *parent) : data(d), bierwirth(b), QWidget(parent)
{

}

void GrapheWindow::paintEvent(QPaintEvent *event)
{
    int width = 60,
        height = 60,
        rayon = width/2,
        x = rayon,
        y = rayon;
    QPainter painter(this);

    QRectF *cercle,
           *duree;
    QLineF *line;

    for(int i=0; i<data->n; ++i)
    {
        x = rayon;
        for(int j=0; j<data->m; ++j)
        {
            cercle = new QRectF(x, y, width, height);
            duree = new QRectF(x + (width+rayon)/2, y-10, width, height);
            line = new QLineF(x+width, y+rayon, x+width+rayon,y+rayon);

            painter.setBrush(Qt::white);
            painter.setPen( Qt::black );
            if (bierwirth->isCritique(&data->operations[i][j]))
            {
                painter.setBrush(Qt::red);
                painter.drawEllipse(*cercle);
                painter.setBrush(Qt::white);
            }
            else
            {
                painter.drawEllipse(*cercle);
            }


            painter.drawText(*cercle, Qt::AlignCenter, "m" + QString::number(data->operations[i][j].getNumeroMachine()));

            painter.drawLine(*line);

            painter.setPen( Qt::red );
            painter.drawText(*duree, Qt::AlignCenter, QString::number(data->operations[i][j].getDuree()));

            x += width + rayon;
        }
        y += height + rayon;
    }
}


