#pragma once
#include <iostream>
#include <time.h>

class Uteis
{
public:
    Uteis();
    virtual ~Uteis();
    static int Aleatorio(int Min, int Max)
    {
        return Min + rand() % (Max - Min + 1);
    }
    static int Aleatorio(int Max)
    {
        return Aleatorio(0, Max);
    }
    static void wait(int mlseconds)
    {
        clock_t endwait;
        endwait = clock() + mlseconds;
        while (clock() < endwait);
    }
};


