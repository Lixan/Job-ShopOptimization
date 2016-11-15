#ifndef OPERATION_H
#define OPERATION_H

#include <string>

/**
 * @brief Gestion des opérations, une machine sur un job.
 */
class Operation
{
public:
    int numeroMachine, numeroJob, duree;
    Operation* pere;

public:
    Operation();
    Operation(int numeroMachine, int numeroJob, int duree);

    std::string toString() const;

    int getNumeroMachine() const;
    int getNumeroJob() const;
    int getDuree() const;
    Operation *getPere() const;

    void setNumeroMachine(int value);
    void setNumeroJob(int value);
    void setDuree(int value);
    void setPere(Operation *value);

    friend class Data;
};

#endif // OPERATION_H
