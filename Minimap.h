////////////////////////////////////////////////////////////////////////////////
//
// Cminimap : classe permetant de generer une minimap à partir d'une map - 
// Chunk
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __DEF_CLASS_MINIMAP_H__
#define __DEF_CLASS_MINIMAP_H__

//#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Chunk.h"
#include "Block.h"
#include "Blocklist.h"

namespace eow
{
    class Cminimap
    {
        private:
        Chunk *m_realMap;
        Image  m_miniMapImg;
        Sprite m_miniMapSpr;
        Cblocklist *m_blocklist;
        
        unsigned int    m_map_w,
                        m_map_h;
        
        public:
        // Constructeur
        Cminimap(Chunk *e_map);
        // Destructeur
        virtual ~Cminimap(void){};
        // Methodes
        void redrawMmap(void);
        Sprite getMmapSpr(void);
    };
}; /* namespace eow */

#endif /* __DEF_CLASS_MINIMAP_H__ */

