#include "Blocklist.h"

namespace eow
{
    // Constructeurs
    Cblocklist::Cblocklist(void)
    {
        // rien à faire
    }

    Cblocklist::Cblocklist(Cblock const& e_block)
    {
        m_blocklist.push_back(new Cblock(e_block));
    }

    // Constructeur par copie
    Cblocklist::Cblocklist(Cblocklist const& e_blocklist) : 
        m_blocklist(e_blocklist.m_blocklist)
    {
        // rien à faire
    }

    // Surgarges d'opérateur
    Cblock* Cblocklist::operator[] (unsigned int x)
    {
        return m_blocklist[x];
    }

    // Methodes
    Cblock Cblocklist::GetBlock(unsigned int x)
    {
        return *m_blocklist[x];
    }

    Color* Cblocklist::GetColor(unsigned int x)
    {
        return m_blockColors[x];
    }

    void Cblocklist::addBlock(Cblock const& e_block)
    {
        m_blocklist.push_back(new Cblock(e_block));
        m_blockColors.push_back(new Color(Color::Black));
    }

    void Cblocklist::addBlock(bool e_grassy, Color e_color)
    {
        unsigned int index = m_blocklist.size();
        m_blocklist.push_back(new Cblock(index, 0, e_grassy));
        m_blockColors.push_back(new Color(e_color));
    }

    unsigned int Cblocklist::getBlocklistSize()
    {
        return m_blocklist.size();
    }
}; /* namespace eow */

