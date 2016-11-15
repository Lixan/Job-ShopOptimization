#include "Operation.h"
#include <iostream>

using namespace std;

Operation::Operation() : numeroMachine(0), numeroJob(0), duree(0), pere(0) {}
Operation::Operation(int numeroMachine, int numeroJob, int duree) : numeroMachine(numeroMachine), numeroJob(numeroJob), duree(duree), pere(0) {}


/**
 * @brief Affichage de l'opération.
 */
std::string Operation::toString() const
{
    std::string chaine;
    chaine += "Op : numero job = "
           + std::to_string(numeroJob)
           + " \t| numero machine = "
           + std::to_string(numeroMachine)
           + "   \t| duree = "
           + std::to_string(duree)
           + "\n";
    return chaine;
}

// ACCESSEURS ==============================================================================================================

int Operation::getNumeroMachine() const
{
    return numeroMachine;
}

void Operation::setNumeroMachine(int value)
{
    numeroMachine = value;
}

int Operation::getNumeroJob() const
{
    return numeroJob;
}

void Operation::setNumeroJob(int value)
{
    numeroJob = value;
}

int Operation::getDuree() const
{
    return duree;
}

void Operation::setDuree(int value)
{
    duree = value;
}

Operation *Operation::getPere() const
{
    return pere;
}

void Operation::setPere(Operation *value)
{
    pere = value;
}
