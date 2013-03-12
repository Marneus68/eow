////////////////////////////////////////////////////////////////////////////////
//
// Chunk : Chunk.h Chunk.cpp : Classe definissant les chunks (portions) de map
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __DEF_CLASS_CHUNK_H__
#define __DEF_CLASS_CHUNK_H__

//#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <cmath>
#include <iostream>

#include "constants.h"
#include "Block.h"
#include "Blocklist.h"
#include "flibrary.h"

using namespace std;
using namespace sf;

namespace eow
{
    class Chunk
    {
        private:
        // Attributs
        unsigned int m_map_w; // largeur
        unsigned int m_map_h; // hauteur
        vector<int> m_strate; // variations de niveau de la strate
        vector<unsigned int> m_border_r; // vector de limite des strates droite
        vector<unsigned int> m_border_l; // vector de limite des strates gauche
        Cblocklist *m_blocklist;
        Cblock* m_CblockTable[(int)MAP_W][(int)MAP_H];
        
        public:
        // Constructeurs
        Chunk(unsigned int e_type, Cblocklist *e_list);
        // Destructeur
        ~Chunk(void);
        
        // Methodes
        // Getters
        Cblock* GetBlock(unsigned int x, unsigned int y);
        // Getters speciaux
        unsigned int getW(void);
        unsigned int getH(void);
        Cblocklist* GetAssociatedList(void);
        // Autres methodes
        // Generation
        void randomize(void);
        void sequence(void); // Crée les strates
        void loopSequence(void); // Crée des trates bouclées
        void fillWith(unsigned int e_type);
        void rockBottom(unsigned int e_type); // trace une ligne au fond du chunk
        // Affectation des blocs
        bool affectBlockSpAt(int x, int y);
        bool affectBlockSpAt(float x, float y);
        bool affectBlockSpAt(float x, float y, int val);
        // Changement du type
        void changeBlockTypeAt(int x, int y, unsigned int e_type);
        void changeBlockTypeAt(float x, float y, unsigned int e_type);
    };
}; /* namespace eown */

#endif /* __DEF_CLASS_CHUNK_H__ */

