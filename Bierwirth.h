#ifndef BIERWIRTH_H
#define BIERWIRTH_H

#include <vector>
#include "Data.h"

class Bierwirth
{
    int n, //nb jobs
        m; //nb machines
    std::vector<int> bierwirth_vector;
    std::vector<int> dateFinJob; //On a pour chaque job sa dernière date d'utilisation par une machine
    std::vector<int> dateFinOperationMachine; //On a pour chaque machine sa dernière date d'utilisation pour un job

    Operation lastOp;

public:
    Bierwirth(int n, int m);
    void shuffle();
    void initializeVectors();
    int evaluate(Data &d);
    void cheminCritique();
    Operation* trouverMachinePrec(std::vector<Operation*> &operations, int operationsSize, int numeroMachine);
};

#endif // BIERWIRTH_H
