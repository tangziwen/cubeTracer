#ifndef TGLASSYMATERIAL_H
#define TGLASSYMATERIAL_H

#include "Tmaterial.h"

class TmirrorMaterial : public Tmaterial
{
public:
    TmirrorMaterial();
    ~TmirrorMaterial();
    virtual float BRDF(Tvector negativeViewDirection, Tvector negativeLightDirection, Tvector normal);
};

#endif // TGLASSYMATERIAL_H
