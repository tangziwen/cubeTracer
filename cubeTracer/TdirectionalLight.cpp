#include "TdirectionalLight.h"
#include "Tray.h"
#include "Tscene.h"
#include <algorithm>
TdirectionalLight::TdirectionalLight(QVector3D dir,float maxIntensity,Tcolor color)
    :m_dir(dir),m_maxIntensity(maxIntensity),m_color(color)
{
    m_dir.normalize ();
}

TdirectionalLight::~TdirectionalLight()
{

}

float TdirectionalLight::getIntensity(int direction)
{
    return m_maxIntensity;
}

float TdirectionalLight::getIrradiance(QVector3D pos, QVector3D normal, Tscene *scene)
{
    auto cosTheta = QVector3D::dotProduct (-m_dir,normal);
    cosTheta = std::max(0.0f,cosTheta);
    auto shadowRay = Tray(pos,-m_dir);
    auto result = scene->intersect (shadowRay);
    if(result.geometry ())
    {
        cosTheta = 0;
    }
    return cosTheta;
}

