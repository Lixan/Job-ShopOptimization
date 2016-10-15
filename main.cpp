#include <iostream>
#include <list>
#include "Data.h"
#include "Bierwirth.h"
#include "Operation.h"

using namespace std;

int main(int, char **)
{
    Data d;
    Operation derniereOperation;
    std::list<Operation*> listeCheminCritique;

    d.lireInstance("../INSTANCES/la01.dat");
    d.affiche();
    std::cout << "==================================" << std::endl << "DATES DE FIN" << std::endl;

    Bierwirth b(d.getN(), d.getM());
    std::cout << "-----> Date de fin au plus tot = " << b.evaluate(d,derniereOperation) << std::endl;
    std::cout << "DERNIERE ";
    derniereOperation.affiche();

    std::cout << "==================================" << std::endl << "CHEMIN CRITIQUE" << std::endl;
    b.cheminCritique(listeCheminCritique, &derniereOperation);

    for (std::list<Operation*>::iterator it = listeCheminCritique.begin(); it != listeCheminCritique.end(); it++)
        (*it)->affiche();
    return 0;
}
