#ifndef TMATERIAL_H
#define TMATERIAL_H

#include "Tcolor.h"
#include "Tray.h"
class Tmaterial
{
public:
    Tmaterial(float reflectiveness, float diffuse, Tcolor diffuseColor);
    ~Tmaterial();
    float reflectiveness() const;
    void setReflectiveness(float reflectiveness);

    float diffuse() const;
    void setDiffuse(float diffuse);

    Tcolor diffuseColor() const;
    void setDiffuseColor(const Tcolor &diffuseColor);

    Tcolor sampleTexture(Tray ray,QVector3D position,QVector3D normal);
private:
    float m_reflectiveness;
    float m_diffuse;
    Tcolor m_diffuseColor;
};

#endif // TMATERIAL_H
