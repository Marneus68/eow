////////////////////////////////////////////////////////////////////////////////
//
// Cspriteman : classe singleton gerant les images. Il attend un grande image 
// qu'il decoupera en different sprites qu'il repartira sous forme de Sprites
// dans des vecteur.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __DEF_CLASS_SPRITEMAN_H__
#define __DEF_CLASS_SPRITEMAN_H__

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

#include <dirent.h>

#include <SFML/Graphics.hpp>

#include "constants.h"

#define GFX_FILE_EXTENT ".png"

using namespace std;
using namespace sf;

namespace eow
{
    typedef Image* ImagePoint;

    class Cspriteman
    {
        private:
        // Attributs
        Image m_sprSheetImg;
        
        Sprite m_sprSheetSpr;
        
        vector<Sprite>  m_subTile,
                        m_subDecal;
        
        vector<ImagePoint>  m_guiImage;
        map<string, Sprite> m_guiElMap;
        
        
        static Cspriteman *_singleton;
        
        // Le destructeur et le constructeurs sont privés, il s'agit d'une classe
        // singleton
        Cspriteman(string const& e_imgPath);
        ~Cspriteman(){};
        
        public:
        // Methodes
        // Getters
        // Retourne le sprite de l'image complette
        Sprite GetImageSpr(void);
        // Retourne un sprite du tableau de sprites
        Sprite  GetTileSpr(unsigned int e_type);
        Sprite  GetDecalSpr(unsigned int e_type);
        Sprite  GetGuiSpr(string const& e_name);
        
        // toString
        string toString(void);
        
        // Methodes statiques, d'initiallisation et de destruction du Singleton
        static Cspriteman *Initialize(string const& e_imgPath);
        static void kill();
    };
}; /* namespace eow */

#endif /* __DEF_CLASS_SPRITEMAN_H__ */

