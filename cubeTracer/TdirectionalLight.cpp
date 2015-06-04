#include "TdirectionalLight.h"
#include "Tray.h"
#include "Tscene.h"
#include <algorithm>
#include <QDebug>
TdirectionalLight::TdirectionalLight(Tvector dir,float maxIntensity,Tcolor color)
    :m_dir(dir),m_maxIntensity(maxIntensity),m_color(color)
{
    m_dir.normalize ();
}

TdirectionalLight::~TdirectionalLight()
{

}

bool TdirectionalLight::isVisible(Tvector pos,Tscene * scene)
{
    auto shadowRay = Tray(pos,-m_dir);
    auto result = scene->intersect (shadowRay);
    if(result.geometry ())
    {
        return false;
    }else
    {
        return true;
    }
}

float TdirectionalLight::getIntensity(int direction)
{
    return m_maxIntensity;
}

Tcolor TdirectionalLight::getIrradiance(Tvector pos, Tvector normal, Tscene *scene)
{
    auto cosTheta = Tvector::dotProduct (-m_dir,normal);
    cosTheta = std::max(0.0f,cosTheta);
    return m_color.modulate (cosTheta);
}

Tcolor TdirectionalLight::color() const
{
    return m_color;
}

void TdirectionalLight::setColor(const Tcolor &color)
{
    m_color = color;
}

Tvector TdirectionalLight::getDir(Tvector pos)
{
    return m_dir;
}


