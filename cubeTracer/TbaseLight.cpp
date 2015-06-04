#include "TbaseLight.h"
#include "Tscene.h"

TexplicitLight::TexplicitLight()
{

}

TexplicitLight::~TexplicitLight()
{

}

QVector3D TexplicitLight::getDir(QVector3D pos)
{
    return QVector3D();
}

float TexplicitLight::getIntensity(int direction)
{
    return 0;
}

bool TexplicitLight::isVisible(QVector3D pos, Tscene *scene)
{
    return false;
}

Tcolor TexplicitLight::getIrradiance(QVector3D pos, QVector3D normal, Tscene *scene)
{
    return Tcolor(1,1,1);
}

