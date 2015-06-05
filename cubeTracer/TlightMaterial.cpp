#include "TlightMaterial.h"

TlightMaterial::TlightMaterial()
{
    setEmission (1);//alway emission;
}

TlightMaterial::~TlightMaterial()
{

}

Tmaterial::MaterialType TlightMaterial::getType()
{
    return MaterialType::Light;
}

float TlightMaterial::BRDF(Tvector negativeViewDirection, Tvector negativeLightDirection, Tvector normal)
{
    return 0;
}

