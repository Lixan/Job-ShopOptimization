#include "mainwindow.h"
#include <QRectF>
#include <QPainter>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QComboBox>
#include <QString>
#include <QPalette>
#include "Data.h"
#include "Bierwirth.h"
#include "bkr.h"
#include "graphewindow.h"
#include "graphedialog.h"
#include <iostream>
#include <QFileInfo>
#include "multistart.h"
#include "geneticalalgorithm.h"

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
    comboBox = new QComboBox(this);
    btnOk = new QPushButton("Lancer",this);

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

    HeuristicMethod * x = new MultiStart();
    HeuristicMethod * y = new GeneticalAlgorithm();
    comboBox->addItem(QString("Multi-Start"), QVariant::fromValue(x));
    comboBox->addItem(QString("Algorithme génétique"), QVariant::fromValue(y));


    //affectations
    scrollArea->setWidget(console);
    scrollArea->setWidgetResizable( true );

    H_layout->addWidget(btn);
    H_layout->addWidget(nomFichier);
    H_layout->addWidget(comboBox);
    H_layout->addWidget(btnOk);

    V_layout->addLayout(H_layout);
    V_layout->addWidget(scrollArea);
    mainWidget->setLayout(V_layout);
    setCentralWidget(mainWidget);

    //Connexions
    QObject::connect(btn,SIGNAL(clicked(bool)),this,SLOT(openDialog()));   
    QObject::connect(btnOk,SIGNAL(clicked(bool)),this,SLOT(lancement()));

    resize(800,500);
    setWindowTitle("Résolution du problème de Job-Shop");
}

void MainWindow::lancement()
{
    if(fileExists(nomFichier->text()))
    {
        afficherGraphe(nomFichier->text());
    }
    else
    {
        console->setText("Sélectionnez un fichier pour démarrer la résolution.");
    }
}

void MainWindow::openDialog()
{
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "*.dat");
    nomFichier->setText(fichier);

}

int MainWindow::afficherGraphe(QString fichier)
{
    Data d;

    d.setName(fichier.toStdString());

    d.lireInstance(fichier.toStdString());
    Bierwirth b(d.getN(), d.getM());    
    QString temp = console->text();
    int dateFin = 0;

    QVariant variant = comboBox->currentData();
    HeuristicMethod *heuristic = variant.value<HeuristicMethod *>();
    dateFin = heuristic->genererMeilleurDate(d, 1000, &b);

    b.cheminCritique();

    BKR bkr(d);

    temp.append("Date de fin = " + QString::number(dateFin) + "\n");
    temp.append("\n\n");
    temp.append(QString::fromStdString(b.toStringCheminCritique()));
    temp.append("\n\n");
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
