#ifndef HEURISTICMETHOD_H
#define HEURISTICMETHOD_H

#include "Data.h"
#include "Bierwirth.h"

class HeuristicMethod
{
public:
    HeuristicMethod();

    virtual int genererMeilleurDate(Data &d, int nbEssais, Bierwirth *best) = 0;
};

#endif // HEURISTICMETHOD_H
