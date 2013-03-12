#include "Chunk.h"

namespace eow
{
    Chunk::Chunk(unsigned int e_type, Cblocklist *e_list) : 
            m_blocklist(e_list)
    {
        m_map_w = MAP_W;
        m_map_h = MAP_H;
        
        unsigned int x, y;
        for (x = 0; x < m_map_w; x++)
        {
            for (y = 0; y < m_map_h; y++)
            {
                Cblock TempBlock;
                TempBlock = m_blocklist->GetBlock(e_type);
                
                // On alloue dynamiquement des portions non contigues de memoire
                // pour contenir les blocks.
                // On range des pointeurs vers les blocks declarés dans un tableau.
                m_CblockTable[x][y] = new Cblock(TempBlock);
                // m_CblockTable est un tableau bidimensionnels de pointeurs vers
                // des objets Cblock.
            }
        }
    }

    // Destructeur
    Chunk::~Chunk(void)
    {
        unsigned int x, y;
        for (x = 0; x < m_map_w; x++)
        {
            for (y = 0; y < m_map_h; y++)
            {
                // On libère l'éspace aloué dynamiquement dans le constructeur.
                delete m_CblockTable[x][y];
            }
        }
    }

    //// Methodes
    // Getters
    Cblock* Chunk::GetBlock(unsigned int x, unsigned int y)
    {
        return m_CblockTable[x][y];
    }

    // Getters speciaux
    unsigned int Chunk::getW(void)
    {
        return m_map_w;
    }

    unsigned int Chunk::getH(void)
    {
        return m_map_h;
    }

    Cblocklist* Chunk::GetAssociatedList(void)
    {
        return m_blocklist;
    }

    // Autres methodes
    void Chunk::randomize(void)
    {
        srand((unsigned)time(0));
        unsigned int x, y;
        for (x = 0; x < m_map_w; x++)
        {
            for (y = 0; y < m_map_h; y++)
            {
                unsigned int randomIndex = Randomizer::Random(1, 4);
                m_CblockTable[x][y]->copyFrom(m_blocklist->GetBlock(randomIndex));
            }
        }
    }

    void Chunk::sequence(void)
    {
        unsigned int x, y;
        
        for (x = 0; x < m_map_w; x++)
        {
            int variance = randStrate(10,80,10);
            if (x != 0)
            {
                m_strate.push_back(variance += m_strate[x - 1]);
            }
            else
            {
                m_strate.push_back(variance);
            }
        }
        
        for (x = 0; x < m_map_w; x++)
        {
            for (y = 90; y < m_map_h; y++)
            {
                if ((y + m_strate[x]) < m_map_h)
                {
                    m_CblockTable[x][y + m_strate[x]]->copyFrom(m_blocklist->GetBlock(1));
                    if (d100(1))
                    {
                         m_CblockTable[x][y + m_strate[x]]->setDecalType(randRange(3,10));
                    }
                    if ((m_CblockTable[x][y + m_strate[x]-1]->getType() == 0))
                    {
                        m_CblockTable[x][y + m_strate[x]]->setGrassy(true);
                    }
                    
                }
            }
            for (y = 125; y < m_map_h; y++)
            {
                if ((y + m_strate[x]) < m_map_h)
                {
                    m_CblockTable[x][y + m_strate[x]]->copyFrom(m_blocklist->GetBlock(2));
                    m_CblockTable[x][y + m_strate[x]]->setDecalType(0);
                    if (d100(1))
                    {
                         m_CblockTable[x][y + m_strate[x]]->setDecalType(randRange(3,9));
                    }
                }
            }
            for (y = 150; y < m_map_h; y++)
            {
                if ((y + m_strate[x]) < m_map_h)
                {
                    m_CblockTable[x][y + m_strate[x]]->copyFrom(m_blocklist->GetBlock(3));
                    m_CblockTable[x][y + m_strate[x]]->setDecalType(0);
                    if (d100(10))
                    {
                         m_CblockTable[x][y + m_strate[x]]->setDecalType(randRange(3,9));
                    }
                }
            }
        }
    }

    void Chunk::loopSequence(void)
    {
        
    }

    void Chunk::fillWith(unsigned int e_type)
    {
        unsigned int x, y;
        for (x = 0; x < m_map_w; x++)
        {
            for (y = 0; y < m_map_h; y++)
            {
                m_CblockTable[x][y]->copyFrom(m_blocklist->GetBlock(e_type));
            }
        }
    }

    void Chunk::rockBottom(unsigned int e_type)
    {
        unsigned int x, y;
        y = m_map_h-1;
        for (x = 0; x < m_map_w; x++)
        {
            m_CblockTable[x][y]->copyFrom(m_blocklist->GetBlock(e_type));
        }
    }
    // Affectation des blocs

    bool Chunk::affectBlockSpAt(int x, int y)
    {
        bool value = true;
        if (x > MAP_W || y > MAP_H)
            value = false;
        else
        {
            m_CblockTable[x][y]->spDecrease();
        }
        return value;
    }

    bool Chunk::affectBlockSpAt(float x, float y)
    {
        bool value = true;
        x = x/BLOCK_W;
        y = y/BLOCK_H;
        if (x > MAP_W || y > MAP_H)
            value = false;
        else
        {
            m_CblockTable[(int) x][(int) y]->spDecrease();
        }
        return value;
    }

    bool Chunk::affectBlockSpAt(float x, float y, int val)
    {
        bool value = true;
        x = x/BLOCK_W;
        y = y/BLOCK_H;
        if (x > MAP_W || y > MAP_H)
            value = false;
        else
        {
            m_CblockTable[(int) ceil(x)][(int) ceil(y)]->setSp(val);
        }
        
        return value;
    }

    void Chunk::changeBlockTypeAt(int x, int y, unsigned int e_type)
    {
        if (x > MAP_W || y > MAP_H)
            return;
        else
        {
            m_CblockTable[x][y]->change(e_type, 1, 0);
        }
    }

    void Chunk::changeBlockTypeAt(float x, float y, unsigned int e_type)
    {
        x = x/BLOCK_W;
        y = y/BLOCK_H;
        if (x > MAP_W || y > MAP_H)
            return;
        else
        {
            m_CblockTable[(int) x][(int) y]->change(e_type, 1, 0);
        }
    }
}; /* namespace eow */

