#include "graphedialog.h"
#include "Data.h"
#include "Bierwirth.h"

GrapheDialog::GrapheDialog(Data &d, Bierwirth &b, QDialog *parent) : QDialog(parent)
{
    int width = 1000,
        height = 600;
    layout = new QVBoxLayout(this);
    graphe = new GrapheWindow(&d,&b,this);
    scrollArea = new QScrollArea(this);

    scrollArea->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOn );
    scrollArea->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOn );

    scrollArea->resize(width,height);
    //scrollArea->setWidgetResizable( true );
    graphe->resize(width*5,height*5);

    graphe->show();
    scrollArea->setWidget(graphe);
    layout->addWidget(scrollArea);
    setLayout(layout);

    resize(width,height);
}
