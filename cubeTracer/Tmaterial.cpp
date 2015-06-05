#include "Tmaterial.h"

Tmaterial::Tmaterial()
    :m_emission(0),m_reflectiveness(1),m_selfTexture(NULL) // default is a pure reflect object.
{

}

Tmaterial::~Tmaterial()
{

}

float Tmaterial::BRDF(Tvector negativeViewDirection, Tvector negativeLightDirection, Tvector normal)
{
    return 1;
}



Tcolor Tmaterial::sampleSelfColor()
{
    if(m_selfTexture)
    {
        return Tcolor(1,1,1);
    }else
    {
        return selfColor ();
    }
}

Tcolor Tmaterial::selfColor() const
{
    return m_selfColor;
}

void Tmaterial::setSelfColor(const Tcolor &selfColor)
{
    m_selfColor = selfColor;
}
Ttexture2D *Tmaterial::selfTexture() const
{
    return m_selfTexture;
}

void Tmaterial::setSelfTexture(Ttexture2D *selfTexture)
{
    m_selfTexture = selfTexture;
}
float Tmaterial::reflectiveness() const
{
    return m_reflectiveness;
}

void Tmaterial::setReflectiveness(float reflectiveness)
{
    m_reflectiveness = reflectiveness;
    m_emission = 1 - reflectiveness;
}
float Tmaterial::emission() const
{
    return m_emission;
}

void Tmaterial::setEmission(float emission)
{
    m_emission = emission;
    m_reflectiveness = 1 - m_emission;
}

Tmaterial::MaterialType Tmaterial::getType()
{
    return MaterialType::Undefined;
}



