#include "flibrary.h"

string float2string(float f)
{
    ostringstream os;
    os << f;
    return os.str();
}

string int2string(int i)
{
    ostringstream os;
    os << i;
    return os.str();
}

string bool2string(bool b)
{
    string ret;
    if (b)
        ret = "true";
    else
        ret = "false";
    return ret;
}

unsigned int randRange(unsigned int a, unsigned int b)
{
    if (a < b)
    {
        unsigned int c = b - a;
        unsigned int r = ((rand()%c)+a);
        return r;
    }
    else if (a > b)
    {
        unsigned int c = a - b;
        unsigned int r = ((rand()%c)+b);
        return r;
    }
    else
    {
        return a;
    }
}

bool d100(unsigned int value)
{
    unsigned int a = (rand()%99);
    if (a < value)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int randStrate(int x, int y, int z)
{
    int total = x + y + z,
        max = 100;
    if (total < max)
    {
        z += (total - max);
    }
    else if (total > max)
    {
        z -= (total - max);
    }
    else
    {
        // Do nothing
    }

    int a = (rand()%(max-1));
    if (a < x)
    {
        return (-1);
    }
    else if (a < y)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

