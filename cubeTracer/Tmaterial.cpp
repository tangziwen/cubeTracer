#include "Tmaterial.h"

Tmaterial::Tmaterial(float reflectiveness, float diffuse, Tcolor diffuseColor)
    :m_reflectiveness(reflectiveness), m_diffuse(diffuse), m_diffuseColor(diffuseColor)
{

}

Tmaterial::~Tmaterial()
{

}
float Tmaterial::reflectiveness() const
{
    return m_reflectiveness;
}

void Tmaterial::setReflectiveness(float reflectiveness)
{
    m_reflectiveness = reflectiveness;
}
float Tmaterial::diffuse() const
{
    return m_diffuse;
}

void Tmaterial::setDiffuse(float diffuse)
{
    m_diffuse = diffuse;
}
Tcolor Tmaterial::diffuseColor() const
{
    return m_diffuseColor;
}

void Tmaterial::setDiffuseColor(const Tcolor &diffuseColor)
{
    m_diffuseColor = diffuseColor;
}

Tcolor Tmaterial::sampleTexture(Tray ray, QVector3D position, QVector3D normal)
{
    return Tcolor(1,1,1);
}




