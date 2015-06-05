#include "TbaseMath.h"

#include <stdlib.h>
double TbaseMath::PI = 3.141592654;

float TbaseMath::randF()
{
    int r = rand()%100;
    return 1.0f * r /100;
}

float TbaseMath::randFN()
{
    return (randF()-0.5f)*2;
}

TbaseMath::TbaseMath()
{

}

TbaseMath::~TbaseMath()
{

}

