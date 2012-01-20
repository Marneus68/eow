////////////////////////////////////////////////////////////////////////////////
//
// Chunk : Chunk.h Chunk.cpp : Classe definissant les chunks (portions) de map
//
////////////////////////////////////////////////////////////////////////////////

#ifndef DEF_CLASS_CHUNK
#define DEF_CLASS_CHUNK

#include <SFML/System.hpp>

#include <vector>
#include <cmath>
#include <iostream>

#include "constants.h"
#include "Block.h"
#include "Blocklist.h"
#include "flibrary.h"

using namespace std;
using namespace sf;

class Chunk
{
    private:
    // Attributs
    unsigned int m_map_w; // largeur
    unsigned int m_map_h; // hauteur
    vector<int> m_strate; // variations de niveau de la strate
    vector<unsigned int> m_border_r; // vector de limite des strates droite
    vector<unsigned int> m_border_l; // vector de limite des strates gauche
    Cblocklist m_blocklist;
    Cblock* m_CblockTable[(int)MAP_W][(int)MAP_H];
    
    public:
    // Constructeurs
    Chunk(unsigned int e_type, Cblocklist &e_list);
    // Destructeur
    ~Chunk();
    
    // Methodes
    // Getters
    Cblock* GetBlock(unsigned int x, unsigned int y);
    // Getters speciaux
    unsigned int getW();
    unsigned int getH();
    // Autres methodes
    // Generation
    void randomize();
    void sequence(); // Crée les strates
    void fillWith(unsigned int e_type);
    void rockBottom(unsigned int e_type); // trace une ligne au fond du chunk
    // Affectation des blocs
    bool affectBlockSpAt(int x, int y);
    bool affectBlockSpAt(float x, float y);
    bool affectBlockSpAt(float x, float y, int val);
    // Changement du type
    void changeBlockTypeAt(int x, int y, unsigned int e_type);
    void changeBlockTypeAt(float x, int y, unsigned int e_type);
};

#endif
