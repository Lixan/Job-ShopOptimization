#include <vector>
#include <fstream>
#include <iostream>
#include "Operation.h"
#include "Data.h"
#include <string>

using namespace std;

Data::Data() { }

/**
 * @brief Lecture d'un fichier de données et récupèration des opérations.
 * @param filename fichier de l'instance
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
 * @brief Affichage de toutes les opérations.
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
 * @brief Affichage des pères des opérations.
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

/**
 * @brief Getter du nombre de jobs.
 * @return nombre de jobs
 */
int Data::getN() const
{
    return n;
}

/**
 * @brief Getter du nombre de machines par jobs.
 * @return nombre de machines
 */
int Data::getM() const
{
    return m;
}

/**
 * @brief Getter du nom de l'instance
 * @return nom de l'instance
 */
std::string Data::getName() const
{
    return name_;
}

/**
 * @brief Setter du nom de l'instance
 * @param name nom de l'instance
 */
void Data::setName(const std::string &name)
{
    name_ = name;
}

