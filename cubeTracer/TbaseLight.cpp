#include "TbaseLight.h"
#include "Tscene.h"

TexplicitLight::TexplicitLight()
{

}

TexplicitLight::~TexplicitLight()
{

}

Tvector TexplicitLight::getDir(Tvector pos)
{
    return Tvector();
}

float TexplicitLight::getIntensity(int direction)
{
    return 0;
}

bool TexplicitLight::isVisible(Tvector pos, Tscene *scene)
{
    return false;
}

Tcolor TexplicitLight::getIrradiance(Tvector pos, Tvector normal, Tscene *scene)
{
    return Tcolor(1,1,1);
}

