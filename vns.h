#ifndef VNS_H
#define VNS_H

#include "heuristicmethod.h"

/**
 * @brief Gestion de la méthode heuristique VNS
 */
class VNS : public HeuristicMethod
{
public:
    VNS();
    int genererMeilleurDate(Data &d, int nbEssais, Bierwirth *best);
};

#endif // VNS_H
