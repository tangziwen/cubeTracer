#ifndef TGLASSYMATERIAL_H
#define TGLASSYMATERIAL_H

#include "Tmaterial.h"

class TglassyMaterial : public Tmaterial
{
public:
    TglassyMaterial();
    ~TglassyMaterial();
    virtual float BRDF(QVector3D viewDirection, QVector3D lightDirection, QVector3D normal);
};

#endif // TGLASSYMATERIAL_H
