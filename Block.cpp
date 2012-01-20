#include "Block.h"

// Constructeur par default
Cblock::Cblock() : 
    m_type(0),
    m_name("Default"),
    m_description("Default"),
    m_sp(1),
    m_grassy(false)
{
    // Rien à faire
}

Cblock::Cblock(unsigned int e_type, string e_name, string e_description, bool e_grassy) : 
    m_type(e_type),
    m_name(e_name),
    m_description(e_description),
    m_sp(1),
    m_grassy(e_grassy)
{
    // Rien à faire
}

// Methodes
// Getters
string Cblock::getName()
{
    return m_name;
}

string Cblock::getDescription()
{
    return m_description;
}

unsigned int Cblock::getType()
{
    return m_type;
}

unsigned int Cblock::getSp()
{
    return m_sp;
}

// Getters speciaux
bool Cblock::isGrassy()
{
    return m_grassy;
}

// Setters
void Cblock::setType(unsigned int e_type)
{
    m_type = e_type;
}

void Cblock::setSp(int e_val)
{
    m_sp = e_val;
}

void Cblock::setGrassy(bool e_grassy)
{
    m_grassy = e_grassy;
}

// Autres methodes
void Cblock::spDecrease()
{
    m_sp--;
}

void Cblock::copyFrom(Cblock& e_Block)
{
    m_type = e_Block.getType();
    m_name = e_Block.getName();
    m_description = e_Block.getDescription();
    m_sp = e_Block.getSp();
}

void Cblock::update()
{
    if (m_sp <= 0)
    {
        m_type = 0;
        m_grassy = false;
    }
}
