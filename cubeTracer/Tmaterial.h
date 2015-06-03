#ifndef TMATERIAL_H
#define TMATERIAL_H

#include "Tcolor.h"
#include "Tray.h"
#include "Ttexture2D.h"
class Tmaterial
{
public:
    Tmaterial(float reflectiveness, float diffuse,float emission, Tcolor diffuseColor);
    ~Tmaterial();
    float reflectiveness() const;
    void setReflectiveness(float reflectiveness);

    float diffuse() const;
    void setDiffuse(float diffuse);

    Tcolor diffuseColor() const;
    void setDiffuseColor(const Tcolor &diffuseColor);

    Tcolor sampleDiffuseTexture(Tray ray,QVector3D position,QVector3D normal);
    Tcolor sampleDiffuseTexture();
    Ttexture2D *diffuseTexture() const;
    void setDiffuseTexture(Ttexture2D *diffuseTexture);

    float emission() const;
    void setEmission(float emission);

private:
    float m_emission;
    float m_reflectiveness;
    float m_diffuse;
    Tcolor m_diffuseColor;
    Ttexture2D * m_diffuseTexture;
};

#endif // TMATERIAL_H
