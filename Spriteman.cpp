#include "Spriteman.h"

// Initialisation du singleton à NULL
Cspriteman *Cspriteman::_singleton = NULL;

// Constructeur
Cspriteman::Cspriteman(string const& e_imgPath, string const& e_decalPath)
{
    unsigned int x, y;
    // On charge les images
    m_sprSheetImg.LoadFromFile(GFX_PATH + e_imgPath);
    m_decalSheetImg.LoadFromFile(GFX_PATH + e_decalPath);

    // Le smoothing c'est mal !
    m_sprSheetImg.SetSmooth(false);
    m_decalSheetImg.SetSmooth(false);
    
    // On crée des sprites à partir des images
    m_decalSheetSpr.SetImage(m_decalSheetImg);
    m_sprSheetSpr.SetImage(m_sprSheetImg);
    
    for (x = 0; x < 10; x++)
    {
        Sprite newSprite(m_sprSheetImg);
        Rect<int> test(x*BLOCK_W,BLOCK_H,(x+1)*BLOCK_W,0);
        newSprite.SetSubRect(test);
        newSprite.SetCenter(0,-BLOCK_H);
        m_subSpr.push_back(newSprite);
        
        Sprite otherNewSprite(m_decalSheetImg);
        Rect<int> test2(x*BLOCK_W,BLOCK_H,(x+1)*BLOCK_W,0);
        otherNewSprite.SetSubRect(test2);
        otherNewSprite.SetCenter(0,-BLOCK_H);
        m_subDecal.push_back(otherNewSprite);
    }
}

// Destructeur
Cspriteman::~Cspriteman()
{
    // Rien à faire
}

// Methodes
// Getters
Sprite Cspriteman::GetImageSpr()
{
    return m_sprSheetSpr;
}

Sprite Cspriteman::GetImageDecal()
{
    return m_decalSheetSpr;
}

Sprite Cspriteman::GetSpr(unsigned int e_type)
{
    return m_subSpr[e_type];
}

Sprite Cspriteman::GetDecal(unsigned int e_type)
{
    return m_subDecal[e_type];
}

// toString
string Cspriteman::toString()
{
    string head, ret;
    if (NULL == _singleton)
    {
        ret = "Singleton de gestion de sprites non crée.";
    }
    else
    {
        ret = "Singleton de gestion de sprites crée à l'adresse";
    }
    return ret;
}

// Methodes statiques
Cspriteman* Cspriteman::Initialize(string const& e_imgPath, string const& e_decalPath)
{
    if (_singleton == NULL)
    {
        _singleton =  new Cspriteman(e_imgPath, e_decalPath);
    }
    else
    {
        // Rien à faire
    }
    return _singleton;
}

void Cspriteman::kill()
{
    if (_singleton != NULL)
    {
        delete _singleton;
        _singleton = NULL;
    }
}
