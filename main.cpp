#include <iostream>
#include <fstream>
#include <ctime>
#include "Data.h"
#include "Bierwirth.h"
#include "Operation.h"

using namespace std;

/**
 * On lit tous les fichiers de tmp situés dans "../INSTANCES"
 * On recupère la meilleure date de fin pour chacun des fichiers
 * On écrit les résultats dans un fichier résultat
 * @brief lireFichiers
 */
void lireFichiers()
{
    string tmp[] = {"la01.dat","la02.dat","la03.dat","la04.dat","la05.dat","la06.dat","la07.dat",
                                             "la08.dat","la09.dat","la10.dat","la11.dat","la12.dat","la13.dat","la14.dat",
                                             "la15.dat","la16.dat","la17.dat","la18.dat","la19.dat","la20.dat"};

   // string tmp[] = {"la01.dat","la06.dat","la07.dat"};

    vector<string> listeFichiers(&tmp[0],&tmp[0]+20);
    ofstream fichier("../resultats.txt");
    Data d;
    const int nbEssais = 1000;

    if(fichier.is_open())
    {
        for(int i=0; i<listeFichiers.size(); ++i)
        {
            d.lireInstance("../INSTANCES/"+listeFichiers[i]);
            Bierwirth b(d.getN(), d.getM());
            fichier << listeFichiers[i] << '\t' << b.getMeilleureDate(d, nbEssais) << endl;
        }
        fichier.close();
    }
    else
    {
        cerr << "Impossible d'ouvrir le fichier" << endl;
    }
}

void testsFonctions()
{
    Data d;
    list<pair<Operation*, Operation*> > pairs;

    d.lireInstance("../INSTANCES/la01.dat");
    d.affiche();
    cout << "==================================" << endl << "DATES DE FIN" << endl;

    Bierwirth b(d.getN(), d.getM());
    cout << "-----> Date de fin au plus tot = " << b.evaluate(d) << endl;
    cout << "DERNIERE ";
    derniereOperation.affiche();

    cout << "==================================" << endl << "CHEMIN CRITIQUE" << endl;
    b.cheminCritique();
    b.afficherCheminCritique();


    cout << "==================" << endl << "Recherche morceaux interessants : " << endl;
    b.rechercheMorceauxInteressants(pairs);

    b.rechercheLocale(d);
}

int main(int, char **)
{
    clock_t begin = clock();

    lireFichiers();

    clock_t end = clock();
    cout << "--> " << double(end - begin) / CLOCKS_PER_SEC << endl;

    return 0;
}
