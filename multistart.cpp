#include "multistart.h"


MultiStart::MultiStart()
{

}


int MultiStart::genererMeilleurDate(Data &d, int nbEssais, Bierwirth *best)
{
    int dateFin,
        dateFinCopie;
    Bierwirth copie(d.getN(), d.getM());

    dateFin = best->rechercheLocale(d);

    for(int i=0;i<nbEssais; ++i)
    {

        copie.shuffle();

        dateFinCopie = copie.rechercheLocale(d);

        if(dateFin > dateFinCopie)
        {
            dateFin = dateFinCopie;
            *best = copie;
        }
    }
    return dateFin;
}
