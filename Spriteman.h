////////////////////////////////////////////////////////////////////////////////
//
// Cspriteman : classe singleton gerant l'image, sa découpe et sa repartition
// en different sprites
//
////////////////////////////////////////////////////////////////////////////////

#ifndef DEF_CLASS_SPRITEMAN
#define DEF_CLASS_SPRITEMAN

#include <iostream>

#include <SFML/Graphics.hpp>

#include <vector>
#include <string>

#include "constants.h"

using namespace std;
using namespace sf;

class Cspriteman
{
    private:
    // Attributs
    Image m_sprSheetImg;
    Image m_decalSheetImg;
    
    Sprite m_sprSheetSpr;
    Sprite m_decalSheetSpr;
    
    vector<Sprite> m_subSpr;
    vector<Sprite> m_subDecal;
    
    static Cspriteman *_singleton;
    
    // Le destructeur et le constructeurs sont privés, il s'agit d'une classe
    // singleton
    Cspriteman(string const& e_imgPath, string const& e_decalPath);
    ~Cspriteman();
    
    public:
    // Methodes
    // Getters
    // Retourne le sprite de l'image complette
    Sprite GetImageSpr();
    Sprite GetImageDecal();
    // Retourne un sprite du tableau de sprites
    Sprite GetSpr(unsigned int e_type);
    Sprite GetDecal(unsigned int e_type);
    // toString
    string toString();
    
    // Methodes statiques, d'initiallisation et de destruction du Singleton
    static Cspriteman *Initialize(string const& e_imgPath, string const& e_decalPath);
    static void kill();
};

#endif
