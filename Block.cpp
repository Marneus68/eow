#include "Block.h"

namespace eow 
{
    // Constructeur par default
    Cblock::Cblock(void) : 
        m_type(0),
        m_sp(1),
        m_grassy(false)
    {
        update();
    }

    Cblock::Cblock(unsigned int e_type, bool e_grassy, unsigned int e_typeDecal) : 
        m_type(e_type),
        m_sp(1),
        m_grassy(e_grassy),
        m_typeDecal(e_typeDecal)
    {
        update();
    }

    // Methodes
    // Getters
    unsigned int Cblock::getType(void)
    {
        return m_type;
    }

    unsigned int Cblock::getDecalType(void)
    {
        return m_typeDecal;
    }

    unsigned int Cblock::getSp(void)
    {
        return m_sp;
    }

    bool Cblock::isGrassy(void)
    {
        return m_grassy;
    }

    // Setters

    void Cblock::change(unsigned int e_type, unsigned int e_sp, unsigned int e_typeDecal)
    {
        m_type = e_type;
        m_sp = e_sp;
        m_grassy = false;
        m_typeDecal = e_typeDecal;
        
        update();
    }

    void Cblock::setType(unsigned int e_type)
    {
        m_type = e_type;
        update();
    }

    void Cblock::setDecalType(unsigned int e_typeDecal)
    {
        m_typeDecal = e_typeDecal;
    }

    void Cblock::setSp(int e_val)
    {
        m_sp = e_val;
        update();
    }

    void Cblock::setGrassy(bool e_grassy)
    {
        m_grassy = e_grassy;
        update();
    }

    // Autres methodes
    void Cblock::spDecrease(void)
    {
        m_sp--;
        update();
    }

    void Cblock::copyFrom(Cblock e_Block)
    {
        m_type = e_Block.getType();
        m_sp = e_Block.getSp();
    }

    void Cblock::update(void)
    {
        if (m_sp <= 0)
        {
            m_type = 0;
            m_grassy = false;
            m_typeDecal = 0;
            
            return;
        }
        
        if (m_grassy == true)
            m_typeDecal = 1;
        else
            m_typeDecal = 0;
    }
}; /* namespace eow */

