#include <iostream>
#include <vector>
#include <algorithm>    // std::random_shuffle
#include "Data.h"
#include "Bierwirth.h"
#include "Operation.h"

Bierwirth::Bierwirth(int n, int m) : n(n), m(m)
{
    bierwirth_vector.reserve(n*m);
    dateFinJob.resize(n);
    dateFinOperationMachine.resize(m);

    initializeVectors();
    shuffle();
}

void Bierwirth::shuffle()
{
    int index = 0;
    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<m; ++j)
        {
            bierwirth_vector[index] = i;
            ++index;
        }
    }
    std::random_shuffle(bierwirth_vector.begin(), bierwirth_vector.end());
}

void Bierwirth::initializeVectors()
{
    int i;
    for(i=0; i<n; ++i)
    {
        dateFinJob[i] = 0;
    }
    for(i=0; i<m; ++i)
    {
        dateFinOperationMachine[i] = 0;
    }
}

int Bierwirth::evaluate(Data &d)
{
    std::vector<int> occurences;
    std::vector<Operation*> operations; //vecteurs contenant toutes les opérations traitées dans l'ordre

    Operation   derniereOperation = d.operations[0][0],
                *pere = 0;
    int i,
        bierwirthSize = n*m,
        idJob, // = ligne = id du job courant traité
        idMachine, //id de la machine courante traitée
        dureeOperation, //valeur de la durée courante traitée
        dateFinMax = 0,
        dateFinAuPlusTot = 0;

    //---- LIGNES A SUPPRIMER ---- Test avec le vecteur de bierwirth du cours
    bierwirth_vector = {0,1,2,0,1,1,2,2,0};
    //bierwirth_vector = {0,5,2,3,4,7,3,7,5,9,6,7,3,0,9,9,5,3,6,8,1,4,1,2,2,8,5,1,9,8,6,7,2,7,0,3,5,8,1,4,1,4,4,6,0,2,6,0,9,8};
    //---- LIGNES A SUPPRIMER ----

    //Initialisation du tableau des opérations effectuées
    operations.resize(bierwirthSize);
    for(i=0; i<bierwirthSize; ++i)
    {
        operations[i] = 0;
    }

    //Initialisation du tableau d'occurences
    occurences.resize(n);
    for(i=0; i<n; ++i)
    {
        occurences[i] = -1;
    }

    // =======================================================
    //début du traitement du vecteur de bierwirth
    for(i=0; i<bierwirthSize; ++i)
    {
        idJob = bierwirth_vector[i];
        ++occurences[idJob];

        //ligne = idJob, colonne = occurences[idJob]
        idMachine = d.operations[idJob][occurences[idJob]].getNumeroMachine();
        dureeOperation = d.operations[idJob][occurences[idJob]].getDuree();

        dateFinMax = std::max(dateFinJob[idJob] + dureeOperation, dateFinOperationMachine[idMachine] + dureeOperation);

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
            pere = trouverMachinePrec(operations,bierwirthSize,idMachine);
            d.operations[idJob][occurences[idJob]].setPere(pere);
        }

        //on stocke l'opération
        operations[i] = &(d.operations[idJob][occurences[idJob]]);

        //std::cout << "(" << dateFinJob[idJob] << ")(" << dateFinOperationMachine[idMachine] << ")(" << dureeOperation << ")" << std::endl;
        dateFinJob[idJob] = dateFinMax;
        dateFinOperationMachine[idMachine] = dateFinMax;

        //std::cout << "Date fin (" << idJob << ";" << occurences[idJob] << ") = " << dateFinMax << std::endl;
    }

    d.affichePeres();

    //on affiche les dates de fin
    for(i=0; i<n; ++i)
    {
        std::cout << "Job " << i << " - date fin = " << dateFinJob[i] << std::endl;
    }
    for(i=0; i<m; ++i)
    {
        std::cout << "Operation machine " << i << " - date fin = " << dateFinOperationMachine[i] << std::endl;
    }

    dateFinAuPlusTot = std::max(*std::max_element(dateFinJob.begin(), dateFinJob.end()), *std::max_element(dateFinOperationMachine.begin(), dateFinOperationMachine.end()));

    return dateFinAuPlusTot;
}

Operation* Bierwirth::trouverMachinePrec(std::vector<Operation*> &operations, int operationsSize, int numeroMachine)
{
    Operation* prec = 0;
    for(int i=0; i<operationsSize; ++i)
    {
        if(operations[i] != 0 && operations[i]->getNumeroMachine() == numeroMachine)
        {
            prec = operations[i];
        }
    }
    return prec;
}

void Bierwirth::cheminCritique()
{

    //tq lastOp != -1 faire
    //  getPere de lastOp
    //  lastOp = pere
    //fait
    //sauvegarde dans un vecteur


    //fonction rechercheLocale : on prend ce vecteur, dedans dès qu'une ligne change entre deux valeurs proches = morceaux interessants.

    //copie de data courant
    //on travaille sur la copie, on cherche dans notre liste de morceaux interessant a permuter les id, on evalue bierwirth : si meilleur il devient le data de base
    //sinon on garde le data qu'on avait avant
    //on va sur le morceaux suivant.
}
