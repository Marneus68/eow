////////////////////////////////////////////////////////////////////////////////
//
// Cmusiceman : classe singleton gerant les musiques. Il attends le chemin vers 
// un dossier, ajoute les musique recurssivement et les stock en fonction de
// leur nom dans une map
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __DEF_CLASS_SOUNDMAN_H__
#define __DEF_CLASS_SOUNDMAN_H__

#include <iostream>
#include <map>
#include <string>

#include <dirent.h>

#include <SFML/Audio.hpp>

#include "constants.h"

#define MUS_FILE_EXTENT ".ogg"

using namespace std;
using namespace sf;

typedef Music* pointMusic;
typedef Sound* pointSound;

namespace eow
{
    class Csoundman
    {
        private:
        // Attributs
        map<string, pointMusic> musicMap;
        map<string, pointSound> soundMap;
        
        static Csoundman *_singleton;
        // Constructeur
        Csoundman();
        // Destructeur
        virtual ~Csoundman();
        
        public:
        // Methodes musiques
        void playMusic(string const& e_musName);
        void stopMusic(string const& e_musName);
        void setLoopMusic(string const& e_musName, bool e_loop);
        // Methodes sons
        void playSound(string const& e_sndName);
        void stopSound(string const& e_sndName);
        void setLoopSound(string const& e_sndName, bool e_loop);
//        string getMusicNames(void);
        
        // Methodes d'initiallisation et de destruction
        static Csoundman *Initialize(void);
        static void kill(void);
    };
}; /* namespace eow */

#endif /* __DEF_CLASS_SOUNDMAN_H__ */

