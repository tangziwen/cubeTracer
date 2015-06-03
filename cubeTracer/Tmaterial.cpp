#include "Tmaterial.h"

Tmaterial::Tmaterial(float reflectiveness, float diffuse, float emission, Tcolor diffuseColor)
    :m_reflectiveness(reflectiveness), m_diffuse(diffuse),m_emission(emission),m_diffuseColor(diffuseColor),m_diffuseTexture(NULL)
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

Tcolor Tmaterial::sampleDiffuseTexture(Tray ray, QVector3D position, QVector3D normal)
{
    if(m_diffuseTexture)
    {
        return Tcolor(1,1,1);
    }else
    {
        return diffuseColor ();
    }
}

Tcolor Tmaterial::sampleDiffuseTexture()
{
    if(m_diffuseTexture)
    {
        return Tcolor(1,1,1);
    }else
    {
        return diffuseColor ();
    }
}
Ttexture2D *Tmaterial::diffuseTexture() const
{
    return m_diffuseTexture;
}

void Tmaterial::setDiffuseTexture(Ttexture2D *diffuseTexture)
{
    m_diffuseTexture = diffuseTexture;
}
float Tmaterial::emission() const
{
    return m_emission;
}

void Tmaterial::setEmission(float emission)
{
    m_emission = emission;
}






