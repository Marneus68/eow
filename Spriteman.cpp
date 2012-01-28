#include "Spriteman.h"

// Initialisation du singleton à NULL
Cspriteman *Cspriteman::_singleton = NULL;

// Constructeur
Cspriteman::Cspriteman(string const& e_imgPath)
{
    unsigned int x, y;
    // On charge l'image
    Sprite m_sprSheetSpr;
    m_sprSheetImg.LoadFromFile(GFX_PATH + e_imgPath);

    // Le smoothing c'est mal !
    m_sprSheetImg.SetSmooth(false);
    
    // On crée des sprites à partir de l'image
    m_sprSheetSpr.SetImage(m_sprSheetImg);

    for (x = 0; x < 30; x++)
    {
        for(y = 0; y < 3; y++)
        {
            Sprite newSprite(m_sprSheetImg);
            Rect<int> test(x*BLOCK_W,(y+1)*BLOCK_H,(x+1)*BLOCK_W,y*BLOCK_H);
            newSprite.SetSubRect(test);
            newSprite.SetCenter(0,-BLOCK_H);
            
            // Selon la ligne à laquelle on est, on sait si il s'agit d'un block
            // ou d'un decal
            if (y >= 0 && y < 1)
            {
                // Il s'agit d'une image de block
                m_subSpr.push_back(newSprite);
            }
            else if (y >= 2)
            {
                // Il s'agit d'un decal
                m_subDecal.push_back(newSprite);
            }
        }
    }

}

// Destructeur
Cspriteman::~Cspriteman()
{
    // Rien à faire
}

// Methodes
// Getters
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
Cspriteman* Cspriteman::Initialize(string const& e_imgPath)
{
    if (_singleton == NULL)
    {
        _singleton =  new Cspriteman(e_imgPath);
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
