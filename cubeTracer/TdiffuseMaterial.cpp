#include "TdiffuseMaterial.h"

TdiffuseMaterial::TdiffuseMaterial()
{

}

TdiffuseMaterial::~TdiffuseMaterial()
{

}

Tmaterial::MaterialType TdiffuseMaterial::getType()
{
    return MaterialType::Diffuse;
}

float TdiffuseMaterial::BRDF(Tvector negativeViewDirection, Tvector negativeLightDirection, Tvector normal)
{
    return 0.7;
}

