////////////////////////////////////////////////////////////////////////////////
//
// Main du projet. Fait appelle à la classe Game pour l'execution du jeu.
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>

#include "Game.h"

int main (int argc, char const* argv[])
{
    eow::Game *theGame;
    
    theGame = eow::Game::Initialize("E.O.W.");
    
    theGame->Run();
    
    return 0;
}
