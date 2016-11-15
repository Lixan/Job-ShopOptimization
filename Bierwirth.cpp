#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <list>
#include "Data.h"
#include "Bierwirth.h"
#include "Operation.h"

using namespace std;

Bierwirth::Bierwirth(int n, int m) : n(n), m(m)
{
    bierwirth_vector.reserve(n*m);
    shuffle();
}

/*!
 * \brief Mélange du vecteur de bierwirth.
 */
void Bierwirth::shuffle()
{
    int     index = 0;
    bierwirth_vector.clear();

    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<m; ++j)
        {
            bierwirth_vector.push_back(i);
            ++index;
        }
    }
    random_shuffle(bierwirth_vector.begin(), bierwirth_vector.end());
}

/*!
 * \brief Mélange du vecteur de bierwirth de k valeurs.
 * \param k nombre de valeurs à mélanger dans le vecteur de bierwirth
 */
void Bierwirth::shuffle(int k)
{
    random_shuffle(bierwirth_vector.begin(), bierwirth_vector.begin()+k);
}

/*!
 * \brief Evaluation du vecteur de bierwirth.
 * \param d instance
 * \return makespan
 */
int Bierwirth::evaluate(Data &d)
{
    vector<int>         occurences;
    vector<Operation*>  dernieresMachines;      //vecteurs contenant toutes les opérations traitées dans l'ordre

    vector<int>         dateFinJob;             //On a pour chaque job sa dernière date d'utilisation par une machine
    vector<int>         dateFinOperationMachine;//On a pour chaque machine sa dernière date d'utilisation pour un job

    int                 i,
                        bierwirthSize = n*m,
                        idJob,                  // = ligne = id du job courant traité
                        idMachine,              //id de la machine courante traitée
                        dureeOperation,         //valeur de la durée courante traitée
                        dateFinMax = 0,         //date fin maximum entre entre la date de fin d'un job et la date de fin d'une machine
                        dateFinAuPlusTot = 0;   //makespan

    //Initialisation du tableau d'occurences et dates de fin des jobs
    occurences.resize(n);
    dateFinJob.resize(n);
    for(i=0; i<n; ++i)
    {
        occurences[i] = -1;
        dateFinJob[i] = 0;
    }

    //Initialisation du tableau des dernières machines utilisées et dates de fin des machines
    dernieresMachines.resize(m);
    dateFinOperationMachine.resize(m);
    for(i=0; i<m; ++i)
    {
        dernieresMachines[i] = 0;
        dateFinOperationMachine[i] = 0;
    }

    // =======================================================
    //début du traitement du vecteur de bierwirth
    lastOp = &d.operations[0][0];

    for(i=0; i<bierwirthSize; ++i)
    {
        idJob = bierwirth_vector[i];
        ++occurences[idJob];

        //ligne = idJob, colonne = occurences[idJob]
        idMachine = d.operations[idJob][occurences[idJob]].getNumeroMachine();
        dureeOperation = d.operations[idJob][occurences[idJob]].getDuree();

        dateFinMax = max(dateFinJob[idJob] + dureeOperation, dateFinOperationMachine[idMachine] + dureeOperation);

        //On détermine détermine le précédent du job
        if(dateFinMax == (dateFinJob[idJob] + dureeOperation))
        {
            if(occurences[idJob]-1 > -1)
            {
                d.operations[idJob][occurences[idJob]].setPere(&d.operations[idJob][occurences[idJob]-1]);
            }
            else
            {
                d.operations[idJob][occurences[idJob]].setPere(0);
            }
        }
        else
        {
            d.operations[idJob][occurences[idJob]].setPere(dernieresMachines[idMachine]);
        }

        //on stocke l'adresse de l'opération utilisée par la machine idMachine (pour les pères)
        dernieresMachines[idMachine] = &d.operations[idJob][occurences[idJob]];

        //mise à jour des dates de fin des jobs et machines
        dateFinJob[idJob] = dateFinMax;
        dateFinOperationMachine[idMachine] = dateFinMax;

        //Si la date de fin de la chaîne augmente, on change la dernière opération (pour le chemin critique)
        if(dateFinMax > dateFinAuPlusTot)
        {
            lastOp = &d.operations[idJob][occurences[idJob]];
            dateFinAuPlusTot = dateFinMax;
        }
    }

    return dateFinAuPlusTot;
}

/*!
 * \brief Calcul du chemin critique.
 */
void Bierwirth::cheminCritique()
{
    Operation   *derniereOperation = lastOp;
    listeCheminCritique.clear();

    while(derniereOperation != 0)
    {
        listeCheminCritique.push_front(derniereOperation);
        derniereOperation = derniereOperation->getPere();
    }
}


/*!
 * \brief Recherche des morceaux/paires intéressants du chemin critique.
 * \param pairs paires d'opérations consécutives qui ne sont pas sur le même job
 */
void Bierwirth::rechercheMorceauxInteressants(list<pair<Operation*, Operation*> > &pairs)
{
    Operation                   *prec = listeCheminCritique.front();
    list<Operation*>::iterator  it = ++listeCheminCritique.begin();

    pairs.clear();

    for (it; it != listeCheminCritique.end(); ++it)
    {
        if(prec->getNumeroJob() != (*it)->getNumeroJob())
        {
            pairs.push_back(pair<Operation*, Operation*>(prec,*it));
        }
        prec = *it;
    }
}


/*!
 * \brief Recherche d'un meilleur makespan.
 * \par   Modification du chemin critique grâce au pairs de morceaux intéressants jusqu'à ce qu'il n'y ait plus d'amélioration du temps.
 * \param d instance
 * \return makespan
 */
int Bierwirth::rechercheLocale(Data &d)
{
    int dateFinPlusTot,
        dateFinPlusTotCopie,
        position1,
        position2;

    bool stopPaires = false,
         stopAlgo = false;

    list<pair<Operation*, Operation*> > pairs;
    list<pair<Operation*, Operation*> >::iterator it;

    Bierwirth copie(n,m);

    dateFinPlusTot = evaluate(d);

    while(!stopAlgo)
    {
        cheminCritique();
        rechercheMorceauxInteressants(pairs);

        it = pairs.begin();
        stopAlgo = true;
        stopPaires = false;

        while(it != pairs.end() && !stopPaires)
        {
            copie = *this;
            position1 = getPositionOperation(d,it->first);
            position2 = getPositionOperation(d,it->second);
            iter_swap(copie.bierwirth_vector.begin() + position1, copie.bierwirth_vector.begin() + position2);

            dateFinPlusTotCopie = copie.evaluate(d);

            if(dateFinPlusTot > dateFinPlusTotCopie)
            {
                *this = copie;
                stopPaires = true;
                stopAlgo = false;
                dateFinPlusTot = dateFinPlusTotCopie;
            }
            ++it;
        }
    }

    evaluate(d);    // on réévalue le vecteur "d" afin de remttre les bons pointeurs sur les pères des opérations
    cheminCritique();

    return dateFinPlusTot;
}


/*!
 * \brief Recherche de la position/index d'une opération dans le vecteur de bierwirth
 * \param d instance
 * \param op opération recherchée
 * \return position/index dans le vecteur
 */
int Bierwirth::getPositionOperation(const Data &d, Operation *op) const
{
    vector<int> occurences;
    int         i,
                bierwirthSize = n*m,
                idJob,
                position = -1;
    bool        fin = false;

    //Initialisation du tableau d'occurences
    occurences.resize(n);
    for(i=0; i<n; ++i)
    {
        occurences[i] = -1;
    }

    // =======================================================
    i=0;
    while(i<bierwirthSize && !fin)
    {
        idJob = bierwirth_vector[i];
        ++occurences[idJob];

        if(&d.operations[idJob][occurences[idJob]] == op)
        {
            fin = true;
            position = i;
        }
        ++i;
    }

    return position;
}


/*!
 * \brief Détermine si l'opération passée en paramètre fait partie du chemin critique.
 * \param op opération
 * \return true si dans le chemin critique, false sinon
 */
bool Bierwirth::isCritique(Operation *op)
{
    return std::find(std::begin(listeCheminCritique), std::end(listeCheminCritique), op) != std::end(listeCheminCritique);
}

/*!
 * \brief Affichage du chemin critique
 * \return
 */
string Bierwirth::toStringCheminCritique() const
{
    string chaine("Chemin critique :\n");
    for (list<Operation*>::const_iterator it = listeCheminCritique.begin(); it != listeCheminCritique.end(); ++it)
    {
        chaine += (*it)->toString();
    }
    chaine += "\n";
    return chaine;
}

/**
 * \brief Affichage du vecteur de bierwirth.
 */
string Bierwirth::afficherVecteurBierwirth() const
{
    std::ostringstream oss;
    oss << "Bierwirth : {";
    for(int j=0; j<bierwirth_vector.size(); ++j)
    {
        oss << bierwirth_vector[j] << ", ";
    }
    oss << "}" << endl;
    return oss.str();
}

