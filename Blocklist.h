////////////////////////////////////////////////////////////////////////////////
//
// Cblocklist : Classe permetant la gestion de la liste des blocks types.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __DEF_CLASS_BLOCKLIST_H__
#define __DEF_CLASS_BLOCKLIST_H__

#include <vector>

#include <SFML/Graphics.hpp>

#include "Block.h"

using namespace std;

namespace eow
{
    class Cblocklist
    {
        private:
        // Attributs
        vector<Cblock*> m_blocklist;
        vector<Color*> m_blockColors;
        
        public:
        // Constructeurs
        Cblocklist(void);
        Cblocklist(Cblock const& e_block);
        // Constructeur par copie
        Cblocklist(Cblocklist const& e_blocklist);
        
        // Surcharge d'opérateur []
        Cblock* operator[] (unsigned int x);
        
        // Methodes
        Cblock GetBlock(unsigned int x);
        Color* GetColor(unsigned int x);
        void addBlock(Cblock const& e_block);
        void addBlock(bool e_grassy, Color e_color);
        unsigned int getBlocklistSize();
    };
}; /* namespace eow */

#endif /* __DEF_CLASS_BLOCKLIST_H__ */

