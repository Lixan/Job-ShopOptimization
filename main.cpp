#include <iostream>
#include "Data.h"
#include "Bierwirth.h"

using namespace std;

int main(int, char **)
{
    Data d;
    d.lireInstance("../INSTANCES/la01.dat");
    d.affiche();
    std::cout << "==================" << std::endl;
    Bierwirth b(d.getN(), d.getM());
    std::cout << "-----> Date de fin au plus tot = " << b.evaluate(d) << std::endl;
    return 0;
}
