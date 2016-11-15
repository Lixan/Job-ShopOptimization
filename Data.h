#ifndef DATA_H
#define DATA_H

#include "Operation.h"
#include <vector>
#include <string>

/*!
 * \brief Gestion de l'instance.
 */
class Data
{
    int n,  //nombre de jobs
        m;  //nombre de machines
    std::vector<std::vector<Operation> > operations;

    std::string name_;

public:
    Data();
    void lireInstance(std::string filename);

    void affiche();
    void affichePeres();

    int getN() const;
    int getM() const;

    std::string getName() const;
    void setName(const std::string &name);

    friend class Bierwirth;
    friend class GrapheWindow;
};

#endif // DATA_H
