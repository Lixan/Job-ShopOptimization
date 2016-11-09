#include "vns.h"

VNS::VNS()
{

}

int VNS::genererMeilleurDate(Data &d, int nbEssais, Bierwirth *best)
{
    int dateFin,
        dateFinCopie,
        k = 0,
        kMax = (d.getN()*d.getM())-1;

    Bierwirth copie(d.getN(), d.getM());

    dateFin = best->rechercheLocale(d);

    while(k != kMax)
    {

        copie.shuffle(k);

        dateFinCopie = copie.rechercheLocale(d);

        if(dateFin > dateFinCopie)
        {
            dateFin = dateFinCopie;
            *best = copie;
            k = 1;
        }
        else
        {
            ++k;
        }
    }
    return dateFin;
}
