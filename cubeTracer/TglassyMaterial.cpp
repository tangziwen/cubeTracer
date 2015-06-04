#include "TglassyMaterial.h"

TglassyMaterial::TglassyMaterial()
{

}

TglassyMaterial::~TglassyMaterial()
{

}

float TglassyMaterial::BRDF(QVector3D viewDirection, QVector3D lightDirection, QVector3D normal)
{
    lightDirection = -lightDirection;
    auto half = (viewDirection + lightDirection).normalized();
    float specAngle =std::max(QVector3D::dotProduct (half, normal), 0.0f);
    float specularPower = pow(specAngle, 4);
    return specularPower;
}

