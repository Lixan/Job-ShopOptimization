#include <vector>
#include <fstream>
#include <iostream>
#include "Operation.h"
#include "Data.h"
#include <string>

using namespace std;

Data::Data() { }

/**
 * On lit un fichier de données et on y récupère ses opérations
 * @brief Data::lireInstance
 * @param filename
 */
void Data::lireInstance(string filename)
{
    ifstream fichier(filename.c_str());
    string str;

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

/**
 * Affichage de toutes les opérations
 * @brief Data::affiche
 */
void Data::affiche()
{
    for(int i=0; i<operations.size(); ++i)
    {
        cout << "Job " << operations[i][0].numeroJob << " : ";
        for(int j=0; j<operations[i].size(); ++j)
        {
            cout << "(" << operations[i][j].numeroMachine << ";" << operations[i][j].duree << ") ";
        }
        cout << endl;
    }
}

/**
 * Affichage des pères des opérations
 * @brief Data::affichePeres
 */
void Data::affichePeres()
{
    for(int i=0; i<operations.size(); ++i)
    {
        for(int j=0; j<operations[i].size(); ++j)
        {
            cout << "Job " << i << "(" << operations[i][j].numeroMachine << ";" << operations[i][j].duree << ") ";
            if(operations[i][j].pere != 0)
            {
                cout << " -----> Pere = (" << operations[i][j].pere->numeroMachine << ";" << operations[i][j].pere->duree << ") " << endl;
            }
            else
            {
                cout << "-----> Pere NULL" << endl;
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
