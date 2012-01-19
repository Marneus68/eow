////////////////////////////////////////////////////////////////////////////////
//
// xxx : flibrary.h flibrary.cpp : Quelques fonctions, separer celles utilisées
// dans le main de celles qui ont attrait au temps et à l'aleatoire, encapsuler
// ces dernièrres dans un singlton dont le constructeur effectue :
// srand((unsigned)time(NULL));
//
////////////////////////////////////////////////////////////////////////////////

#ifndef DEF_FUNDAMENTAL
#define DEF_FUNDAMENTAL

#include <cstdlib>
#include <ctime>
#include <sstream>
#include <string>

using namespace std;

string float2string(float f);
string int2string(int i);
unsigned int randRange(unsigned int a, unsigned int b);
bool d100(unsigned int value);
int randStrate(int x, int y, int z);

#endif
