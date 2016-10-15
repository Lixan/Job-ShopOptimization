#include <vector>
#include <fstream>
#include <iostream>
#include "Operation.h"
#include "Data.h"
#include <string>

Data::Data() { }

void Data::lireInstance(std::string filename)
{
    std::ifstream fichier(filename.c_str());
    std::string str;

    if(!fichier.fail())
    {
        getline(fichier,str);
        fichier >> n >> m;
        operations.resize(n);

        for(int i=0; i<n; ++i)
        {
            operations[i].resize(m);
            for(int j=0; j<m; ++j)
            {
                fichier >> operations[i][j].numeroMachine >> operations[i][j].duree;
                operations[i][j].numeroJob = i;
            }
        }

        fichier.close();
    }
}

void Data::affiche()
{
    for(int i=0; i<operations.size(); ++i)
    {
        std::cout << "Job " << operations[i][0].numeroJob << " : ";
        for(int j=0; j<operations[i].size(); ++j)
        {
            std::cout << "(" << operations[i][j].numeroMachine << ";" << operations[i][j].duree << ") ";
        }
        std::cout << std::endl;
    }
}

void Data::affichePeres()
{
    for(int i=0; i<operations.size(); ++i)
    {
        for(int j=0; j<operations[i].size(); ++j)
        {
            std::cout << "Job " << i << "(" << operations[i][j].numeroMachine << ";" << operations[i][j].duree << ") ";
            if(operations[i][j].pere != 0)
            {
                std::cout << " -----> Pere = (" << operations[i][j].pere->numeroMachine << ";" << operations[i][j].pere->duree << ") " << std::endl;
            }
            else
            {
                std::cout << "-----> Pere NULL" << std::endl;
            }
        }
    }
}

int Data::getN() const
{
    return n;
}

int Data::getM() const
{
    return m;
}
