#ifndef MULTISTART_H
#define MULTISTART_H

#include "heuristicmethod.h"

class MultiStart : public HeuristicMethod
{
public:
    MultiStart();
    int genererMeilleurDate(Data &d, int nbEssais, Bierwirth *best);
};

#endif // MULTISTART_H
