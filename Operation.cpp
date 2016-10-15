#include "Operation.h"

Operation::Operation() : numeroMachine(0), numeroJob(0), duree(0), pere(0) {}
Operation::Operation(int numeroMachine, int numeroJob, int duree) : numeroMachine(numeroMachine), numeroJob(numeroJob), duree(duree), pere(0) {}


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
