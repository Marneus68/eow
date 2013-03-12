////////////////////////////////////////////////////////////////////////////////
//
// Cblock : Block.h Block.cpp : Classe definissant les blocks de jeu
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __DEF_CLASS_BLOCK_H__
#define __DEF_CLASS_BLOCK_H__

#include <string>

#include <SFML/Graphics.hpp>

#include "constants.h"

using namespace sf;
using namespace std;

namespace eow
{
    class Cblock
    {
        private:
        // Attributs
        unsigned int m_type; // Type du bloc
        unsigned int m_typeDecal; // Type de decalcomanie
        unsigned int m_sp; // Points de structure
        bool m_grassy;
        
        public:
        // Constructeurs
        Cblock(void);
        Cblock(unsigned int e_type, bool e_grassy, unsigned int e_typeDecal);
        
        // Methodes
        // Getters
        unsigned int getType(void);
        unsigned int getDecalType(void);
        unsigned int getSp(void);
        bool isGrassy(void);
        // Setters
        void change(unsigned int e_type, unsigned int e_sp, unsigned int e_typeDecal);
        void setType(unsigned int e_type);
        void setDecalType(unsigned int e_typeDecal);
        void setSp(int e_val);
        void setGrassy(bool e_grassy);
        // Autres methodes
        void spDecrease(void);
        void copyFrom(Cblock e_Block);
        void update(void); // Met à jour le bloc
    };
}; /* namespace eow */

#endif /* __DEF_CLASS_BLOCK_H__ */

