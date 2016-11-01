#ifndef BIERWIRTH_H
#define BIERWIRTH_H

#include <vector>
#include <list>
#include "Data.h"
#include <string>

class Bierwirth
{
    int n, //nb jobs
        m; //nb machines
    std::vector<int> bierwirth_vector;
    std::list<Operation*> listeCheminCritique;

    Operation *lastOp;

public:
    Bierwirth(int n, int m);

    void shuffle();

    int evaluate(Data &d);
    void cheminCritique();
    int rechercheLocale(Data &d);
    int getMeilleureDate(Data &d1, int nbEssais);

    void rechercheMorceauxInteressants(std::list<std::pair<Operation*, Operation*> > &pairs);
    int getPositionOperation(const Data &d, Operation *op) const;
    bool isCritique(Operation *op);

    std::string toStringCheminCritique() const;
    void afficherCheminCritique() const;
    void afficherVecteurBierwirth() const;

    friend class GrapheWindow;
};

#endif // BIERWIRTH_H
