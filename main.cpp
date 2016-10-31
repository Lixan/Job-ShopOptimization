#include <QApplication>
#include "mainwindow.h"
#include "graphewindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow fenetre;
    fenetre.show();

    return app.exec();
}
