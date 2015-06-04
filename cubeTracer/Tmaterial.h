#ifndef TMATERIAL_H
#define TMATERIAL_H
#include "Tcolor.h"
#include "Ttexture2D.h"
#include <qvector3d.h>
class Tmaterial
{
public:
    Tmaterial();
    ~Tmaterial();

    virtual Tcolor sampleSelfColor();

    virtual float BRDF(QVector3D viewDirection,QVector3D lightDirection,QVector3D normal);

    Tcolor selfColor() const;
    void setSelfColor(const Tcolor &selfColor);
    Ttexture2D *selfTexture() const;
    void setSelfTexture(Ttexture2D *selfTexture);

    float reflectiveness() const;
    void setReflectiveness(float reflectiveness);

    float emission() const;
    void setEmission(float emission);

protected:
    Tcolor m_selfColor;
    Ttexture2D * m_selfTexture;
    float m_emission;
    float m_reflectiveness;
};

#endif // TMATERIAL_H
