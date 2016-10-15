#ifndef OPERATION_H
#define OPERATION_H

class Operation
{
public:
    int numeroMachine, numeroJob, duree;
    Operation* pere;

public:
    Operation();
    Operation(int numeroMachine, int numeroJob, int duree);
    void affiche() const;

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
