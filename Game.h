////////////////////////////////////////////////////////////////////////////////
//
// Game : singleton
// Classe encapsulant le moteur du jeu
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __CLASS_GAME_H__
#define __CLASS_GAME_H__

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "constants.h"
#include "flibrary.h"

#include "Chunk.h"
#include "Block.h"
#include "Blocklist.h"
#include "Spriteman.h"
#include "Soundman.h"
#include "Minimap.h"

using namespace sf;
using namespace std;

namespace eow
{
    class Game
    {
        private:
        /* membres */
        static Game *_singleton;
        string m_title;
        int m_exitStatus;
        /* membres issus de SFML */
        sf::RenderWindow    renderWindow;
        sf::Font            pixelFont;
        sf::Event           Event;
        sf::Image           screenCap;
        
        eow::Cspriteman     *spriteman;
        eow::Csoundman      *musicman;
        eow::Cblocklist     blocklist;
        eow::Chunk          *map;
        
        /* autres membres pour le jeu */
        bool    inventory;
        
        int showmmap,
            bgdecal;
        
        /* Runtime methods */
        void pre_init(void);
        void init(void);
        void main_loop(void);
        void cleanup(void);
        
        /* Methodes internes */
        void drawLoop(eow::Chunk * map);
        void drawDebug();
        
        /* Constructeur */
        Game(string const& e_title);
        /* Destructeur */
        virtual ~Game(){};
        
        public:
        static Game *Initialize(string const& e_title);
        static void kill(void);
        
        void Run(void);
    };
}; /* namespace eow */


#endif /* __CLASS_GAME_H__ */

