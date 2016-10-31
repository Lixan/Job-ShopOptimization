#include "mainwindow.h"
#include <QRectF>
#include <QPainter>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QPalette>
#include "Data.h"
#include "Bierwirth.h"
#include "bkr.h"
#include "graphewindow.h"
#include "graphedialog.h"
#include <iostream>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    //Créations
    mainWidget = new QWidget(this);
    H_layout = new QHBoxLayout;
    V_layout = new QVBoxLayout;

    btn = new QPushButton("Sélectionner fichier...",this);
    nomFichier = new QLabel("aucun fichier sélectionné",this);
    scrollArea = new QScrollArea(this);
    console = new QLabel(this);

    //Initialisations
    scrollArea->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOn );
    scrollArea->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOn );

    btn->setFixedHeight(50);
    btn->setMaximumWidth(300);
    btn->setCursor(Qt::PointingHandCursor);

    //changement background color de console
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::white);
    scrollArea->setAutoFillBackground(true);
    scrollArea->setPalette(Pal);

    console->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    //affectations
    scrollArea->setWidget(console);
    scrollArea->setWidgetResizable( true );

    H_layout->addWidget(btn);
    H_layout->addWidget(nomFichier);

    V_layout->addLayout(H_layout);
    V_layout->addWidget(scrollArea);
    mainWidget->setLayout(V_layout);
    setCentralWidget(mainWidget);

    //Connexions
    QObject::connect(btn,SIGNAL(clicked(bool)),this,SLOT(openDialog()));

    resize(800,500);
    setWindowTitle("TP2 - Aide à la décision");
}

void MainWindow::openDialog()
{
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "*.dat");
    nomFichier->setText(fichier);

    if(fileExists(fichier))
    {
        afficherGraphe(fichier);
    }
}

int MainWindow::afficherGraphe(QString fichier)
{
    Data d;

    d.setName(fichier.toStdString());

    d.lireInstance(fichier.toStdString());
    Bierwirth b(d.getN(), d.getM());    
    QString temp = console->text();
    int dateFin = 0;

    dateFin = b.getMeilleureDate(d, 1000);
    b.cheminCritique();

    BKR bkr(d);

    temp.append("\n\n===============================================\n");
    temp.append("Date de fin = " + QString::number(dateFin) + "\n");
    temp.append("\n\n===============================================\n\n");
    temp.append(QString::fromStdString(b.toStringCheminCritique()));
    temp.append("\n\n===============================================\n\n");
    temp.append("Solution approchée à " + QString::number(100 *((float)bkr.makespan_/dateFin)) +"% de la meilleure solution : "+ QString::number(bkr.makespan_) +".\n");
    temp.append("\n\n===============================================\n\n");
    console->setText(temp);

    GrapheDialog gd(d,b);
    return gd.exec();
}

bool MainWindow::fileExists(QString path) {
    QFileInfo check_file(path);
    // check if file exists and if yes: Is it really a file and no directory?
    return check_file.exists() && check_file.isFile();
}
