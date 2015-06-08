#include "TmirrorMaterial.h"
#include <algorithm>
#include <math.h>
TmirrorMaterial::TmirrorMaterial()
{

}

TmirrorMaterial::~TmirrorMaterial()
{

}

Tmaterial::MaterialType TmirrorMaterial::getType()
{
    return MaterialType::Mirror;
}

float TmirrorMaterial::BRDF(Tvector negativeViewDirection, Tvector negativeLightDirection, Tvector normal)
{
    auto reflect = Tvector::reflect (-negativeLightDirection,normal);
    float spec = Tvector::dotProduct (reflect,negativeViewDirection);
    if(fabs(spec - 1.0f) <0.00001)
    {
        return 0.9;
    }else
    {
        return 0;
    }

}

