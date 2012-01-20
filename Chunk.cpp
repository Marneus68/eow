#include "Chunk.h"

Chunk::Chunk(unsigned int e_type, Cblocklist &e_list) : m_blocklist(e_list)
{
    m_map_w = MAP_W;
    m_map_h = MAP_H;

    unsigned int x, y;
    for (x = 0; x < m_map_w; x++)
    {
        for (y = 0; y < m_map_h; y++)
        {
            Cblock TempBlock;
            TempBlock = m_blocklist.GetBlock(e_type);
            
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
Chunk::~Chunk()
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
unsigned int Chunk::getW()
{
    return m_map_w;
}

unsigned int Chunk::getH()
{
    return m_map_h;
}

// Autres methodes
void Chunk::randomize()
{
    srand((unsigned)time(0));
    unsigned int x, y;
    for (x = 0; x < m_map_w; x++)
    {
        for (y = 0; y < m_map_h; y++)
        {
//            int randomIndex = rand()%3 ;
            unsigned int randomIndex = Randomizer::Random(1, 4);
            m_CblockTable[x][y]->copyFrom(*m_blocklist[randomIndex]);
        }
    }
}

void Chunk::sequence()
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
                m_CblockTable[x][y + m_strate[x]]->copyFrom(*m_blocklist[1]);
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
                m_CblockTable[x][y + m_strate[x]]->copyFrom(*m_blocklist[2]);
            }
        }
        for (y = 150; y < m_map_h; y++)
        {
            if ((y + m_strate[x]) < m_map_h)
            {
                m_CblockTable[x][y + m_strate[x]]->copyFrom(*m_blocklist[3]);
            }
        }
    }
}

void Chunk::fillWith(unsigned int e_type)
{
    unsigned int x, y;
    for (x = 0; x < m_map_w; x++)
    {
        for (y = 0; y < m_map_h; y++)
        {
            m_CblockTable[x][y]->copyFrom(*m_blocklist[e_type]);
        }
    }
}

void Chunk::rockBottom(unsigned int e_type)
{
    unsigned int x;
    for (x = 0; x < m_map_w; x++)
    {
        m_CblockTable[x][m_map_h-1]->copyFrom(*m_blocklist[e_type]);
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
        m_CblockTable[x][y]->update();
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
        m_CblockTable[(int) x][(int) y]->update();
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
        m_CblockTable[(int) x][(int) y]->update();
    }
    
    return value;
}

void Chunk::changeBlockTypeAt(int x, int y, unsigned int e_type)
{
    if (x > MAP_W || y > MAP_H)
        return;
    else
    {
        m_CblockTable[x][y]->setType(e_type);
        m_CblockTable[x][y]->setSp(1);
        m_CblockTable[x][y]->update();
    }
}

void Chunk::changeBlockTypeAt(float x, int y, unsigned int e_type)
{
    x = x/BLOCK_W;
    y = y/BLOCK_H;
    if (x > MAP_W || y > MAP_H)
        return;
    else
    {
        m_CblockTable[(int) x][(int) y]->setType(e_type);
        m_CblockTable[(int) x][(int) y]->setSp(1);
        m_CblockTable[(int) x][(int) y]->update();
    }
}
