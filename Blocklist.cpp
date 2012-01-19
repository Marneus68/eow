#include "Blocklist.h"

// Constructeurs
Cblocklist::Cblocklist()
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

void Cblocklist::addBlock(Cblock const& e_block)
{
    m_blocklist.push_back(new Cblock(e_block));
}

void Cblocklist::addBlock(string e_name, string e_description, bool e_grassy)
{
    unsigned int index = m_blocklist.size();
    m_blocklist.push_back(new Cblock(index, e_name, e_description, e_grassy));
}

unsigned int Cblocklist::getBlocklistSize()
{
    return m_blocklist.size();
}
