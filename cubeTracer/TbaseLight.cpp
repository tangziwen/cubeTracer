#include "TbaseLight.h"
#include "Tscene.h"

TbaseLight::TbaseLight()
{

}

TbaseLight::~TbaseLight()
{

}

QVector3D TbaseLight::getDir(QVector3D pos)
{
    return QVector3D();
}

float TbaseLight::getIntensity(int direction)
{
    return 0;
}

bool TbaseLight::isVisible(QVector3D pos, Tscene *scene)
{
    return false;
}

Tcolor TbaseLight::getIrradiance(QVector3D pos, QVector3D normal, Tscene *scene)
{
    return Tcolor(1,1,1);
}

