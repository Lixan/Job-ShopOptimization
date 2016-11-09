#include "mainwindow.h"
#include <QPushButton>
#include <QFileDialog>
#include <QComboBox>
#include <QString>
#include <QPalette>
#include <iostream>
#include <QFileInfo>

#include "multistart.h"
#include "vns.h"
#include "graphewindow.h"
#include "bkr.h"
#include "Data.h"
#include "Bierwirth.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    //Créations
    mainWidget = new QWidget(this);
    H_layout_top = new QHBoxLayout;
    H_layout_bottom = new QHBoxLayout;
    V_layout = new QVBoxLayout;

    btn = new QPushButton("Sélectionner fichier...",this);
    nomFichier = new QLabel("aucun fichier sélectionné",this);
    scrollAreaConsole = new QScrollArea(this);
    scrollAreaGraphe = new QScrollArea(this);
    console = new QLabel(this);
    comboBox = new QComboBox(this);
    btnOk = new QPushButton("Lancer",this);

    //Initialisations
    scrollAreaConsole->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOn );
    scrollAreaConsole->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOn );
    scrollAreaGraphe->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOn );
    scrollAreaGraphe->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOn );

    btn->setFixedHeight(50);
    btn->setMaximumWidth(300);
    btn->setCursor(Qt::PointingHandCursor);

    //changement background color de console
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::white);
    scrollAreaConsole->setAutoFillBackground(true);
    scrollAreaConsole->setPalette(Pal);

    console->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    HeuristicMethod * x = new MultiStart();
    HeuristicMethod * y = new VNS();
    comboBox->addItem(QString("Multi-Start"), QVariant::fromValue(x));
    comboBox->addItem(QString("VNS"), QVariant::fromValue(y));


    //affectations
    scrollAreaConsole->setWidget(console);
    scrollAreaConsole->setWidgetResizable( true );

    H_layout_top->addWidget(btn);
    H_layout_top->addWidget(nomFichier);
    H_layout_top->addWidget(comboBox);
    H_layout_top->addWidget(btnOk);

    H_layout_bottom->addWidget(scrollAreaConsole);
    H_layout_bottom->addWidget(scrollAreaGraphe);

    V_layout->addLayout(H_layout_top);
    V_layout->addLayout(H_layout_bottom);
    mainWidget->setLayout(V_layout);
    setCentralWidget(mainWidget);

    //Connexions
    QObject::connect(btn,SIGNAL(clicked(bool)),this,SLOT(openDialog()));   
    QObject::connect(btnOk,SIGNAL(clicked(bool)),this,SLOT(lancement()));

    resize(800,500);
    setWindowTitle("Résolution du problème de Job-Shop");
}

/**
 * Lancement du traitement du fichier sélectionné
 * @brief MainWindow::lancement
 */
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

/**
 * Ouvre une fenêtre de dialogue pour la sélection du fichier du données
 * @brief MainWindow::openDialog
 */
void MainWindow::openDialog()
{
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "*.dat");
    nomFichier->setText(fichier);

}

/**
 * Crée Data + Bierwirth, effectue les opérations sur le vecteur de bierwirth
 * et affiche les résultats dans la console + le graphe
 * @brief MainWindow::afficherGraphe
 * @param fichier : fichier contenant les données du job-shop
 */
void MainWindow::afficherGraphe(QString fichier)
{
    //Création de Data et lecture du fichier
    d = new Data;
    d->setName(fichier.toStdString());
    d->lireInstance(fichier.toStdString());

    //Création du vecteur de Bierwirth
    b = new Bierwirth(d->getN(), d->getM());
    QString temp = console->text();
    int dateFin = 0;

    //Choix de la méthode d'évaluation
    QVariant variant = comboBox->currentData();
    HeuristicMethod *heuristic = variant.value<HeuristicMethod *>();

    //Génération des données
    dateFin = heuristic->genererMeilleurDate(*d, 1000, b);
    b->cheminCritique();

    BKR bkr(*d);

    //Affichage dans la console
    temp.append("Date de fin = " + QString::number(dateFin) + "\n");
    temp.append("\n\n");
    temp.append(QString::fromStdString(b->toStringCheminCritique()));
    temp.append("\n\n");
    temp.append("Solution approchée à " + QString::number(100 *((float)bkr.makespan_/dateFin)) +"% de la meilleure solution : "+ QString::number(bkr.makespan_) +".\n");
    temp.append("\n\n===============================================\n\n");
    console->setText(temp);

    //Affichage du graphe
    graphe = new GrapheWindow(d,b,this);
    graphe->resize(5000,5000);
    graphe->show();
    scrollAreaGraphe->setWidget(graphe);
}

/**
 * Retourne true si le fichier de chemin path existe
 * @brief MainWindow::fileExists
 * @param path
 * @return
 */
bool MainWindow::fileExists(QString path) {
    QFileInfo check_file(path);
    // check if file exists and if yes: Is it really a file and no directory?
    return check_file.exists() && check_file.isFile();
}
