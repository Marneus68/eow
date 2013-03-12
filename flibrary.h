////////////////////////////////////////////////////////////////////////////////
//
// xxx : flibrary.h flibrary.cpp : Quelques fonctions.
// TODO :separer celles utilisées
// dans le main de celles qui ont attrait au temps et à l'aleatoire, encapsuler
// ces dernièrres dans une classe dont le constructeur effectue :
// srand((unsigned)time(NULL));
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __DEF_FUNDAMENTAL_H__
#define __DEF_FUNDAMENTAL_H__

#include <cstdlib>
#include <ctime>
#include <sstream>
#include <string>

using namespace std;

string float2string(float f);
string int2string(int i);
string bool2string(bool b);
unsigned int randRange(unsigned int a, unsigned int b);
bool d100(unsigned int value);
int randStrate(int x, int y, int z);

#endif /* __DEF_FUNDAMENTAL_H__ */

