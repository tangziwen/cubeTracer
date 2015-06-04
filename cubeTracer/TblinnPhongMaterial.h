#ifndef TBLINN_PHONG_MATERIAL_H
#define TBLINN_PHONG_MATERIAL_H

#include "Tcolor.h"
#include "Tray.h"
#include "Tmaterial.h"
class TblinnPhongMaterial: public Tmaterial
{
public:
    TblinnPhongMaterial(float diffusePower, float shinnes);
    ~TblinnPhongMaterial();

    virtual float BRDF(QVector3D viewDirection, QVector3D lightDirection, QVector3D normal);

    float shininess() const;
    void setShininess(float shininess);

    float diffusePower() const;
    void setDiffusePower(float diffusePower);

private:
    float m_diffusePower;
    float m_shininess;
};

#endif // TMATERIAL_H
