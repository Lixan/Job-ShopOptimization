#ifndef GENETICALALGORITHM_H
#define GENETICALALGORITHM_H

#include "heuristicmethod.h"

class GeneticalAlgorithm : public HeuristicMethod
{
public:
    GeneticalAlgorithm();
    int genererMeilleurDate(Data &d, int nbEssais, Bierwirth *best);
};

#endif // GENETICALALGORITHM_H
