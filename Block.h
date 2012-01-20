////////////////////////////////////////////////////////////////////////////////
//
// Cblock : Block.h Block.cpp : Classe definissant les blocks de jeu
//
////////////////////////////////////////////////////////////////////////////////

#ifndef DEF_CLASS_BLOCK
#define DEF_CLASS_BLOCK

#include <string>

#include <SFML/Graphics.hpp>

#include "constants.h"

using namespace sf;
using namespace std;

class Cblock
{
    private:
    // Attributs
    string m_name;
    string m_description;
    unsigned int m_type; // Type du bloc
    unsigned int m_sp; // Points de structure
    bool m_grassy;
    
    public:
    // Constructeurs
    Cblock();
    Cblock(unsigned int e_type, string e_name, string e_description, bool e_grassy);
    
    // Methodes
    // Getters
    string getName();
    string getDescription();
    unsigned int getType();
    unsigned int getSp();
    bool isGrassy();
    // Setters
    void setType(unsigned int e_type);
    void setSp(int e_val);
    void setGrassy(bool e_grassy);
    // Autres methodes
    void spDecrease();
    void copyFrom(Cblock& e_Block);
    void update(); // Met à jour le bloc
};

#endif
