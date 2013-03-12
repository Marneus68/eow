#include "Minimap.h"

namespace eow
{
    Cminimap::Cminimap(Chunk *e_map) : 
        m_realMap(e_map),
        m_blocklist(e_map->GetAssociatedList())
    {
        m_miniMapImg.SetSmooth(false);
        m_miniMapImg.Create(MAP_W, MAP_H, *m_blocklist->GetColor(0));
        
        m_miniMapSpr.SetImage(m_miniMapImg);
        
        m_map_w = m_realMap->getW();
        m_map_h = m_realMap->getH();
        
        redrawMmap();
    }
    
    void Cminimap::redrawMmap(void)
    {
        unsigned int x, y;
        for (x = 0; x < m_map_w; x++)
        {
            for (y = 0; y < m_map_h; y++)
            {
                Cblock *tempBlock = m_realMap->GetBlock(x, y);
                int tempType = tempBlock->getType();
                
                m_miniMapImg.SetPixel(x, y, *m_blocklist->GetColor(tempType));
            }
        }
    }
    
    Sprite Cminimap::getMmapSpr(void)
    {
        redrawMmap();
        return m_miniMapSpr;
    }
}; /* namespace eow */

