#ifndef DATA_H
#define DATA_H

#include "Operation.h"
#include <vector>
#include <string>

class Data
{
    int n,  //nombre de jobs
        m;  //nombre de machines
    std::vector<std::vector<Operation> > operations;

public:
    Data();
    void lireInstance(std::string filename);
    void affiche();
    void affichePeres();

    int getN() const;
    int getM() const;

    friend class Bierwirth;
};

#endif // DATA_H
