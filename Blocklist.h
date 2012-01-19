////////////////////////////////////////////////////////////////////////////////
//
// Cblocklist : Classe permetant la gestion de la liste des blocks types.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef DEF_CLASS_BLOCKLIST
#define DEF_CLASS_BLOCKLIST

#include <vector>

#include <SFML/Graphics.hpp>

#include "Block.h"

using namespace std;

typedef vector<Image> Cimagelist;

class Cblocklist
{
    private:
    // Attributs
    vector<Cblock*> m_blocklist;
    
    public:
    // Constructeurs
    Cblocklist();
    Cblocklist(Cblock const& e_block);
    // Constructeur par copie
    Cblocklist(Cblocklist const& e_blocklist);
    
    // Surcharges d'opérateur
    Cblock* operator[] (unsigned int x);
    
    // Methodes
    Cblock GetBlock(unsigned int x);
    void addBlock(Cblock const& e_block);
    void addBlock(string e_name, string e_description, bool e_grassy);
    unsigned int getBlocklistSize();
};

#endif

