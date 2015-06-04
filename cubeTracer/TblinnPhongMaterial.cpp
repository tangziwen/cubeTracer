#include "TblinnPhongMaterial.h"

#include <math.h>
#include <algorithm>
TblinnPhongMaterial::TblinnPhongMaterial(float diffusePower, float shinnes)
    :m_diffusePower(diffusePower),m_shininess(shinnes)
{

}

TblinnPhongMaterial::~TblinnPhongMaterial()
{

}

float TblinnPhongMaterial::BRDF(Tvector negativeViewDirection, Tvector negativeLightDirection, Tvector normal)
{
    auto half = (negativeViewDirection + negativeLightDirection).normalized();
    float specAngle =std::max(Tvector::dotProduct (half, normal), 0.0f);
    float specularPower = pow(specAngle, m_shininess);
    return specularPower + m_diffusePower;
}

float TblinnPhongMaterial::shininess() const
{
    return m_shininess;
}

void TblinnPhongMaterial::setShininess(float shininess)
{
    m_shininess = shininess;
}
float TblinnPhongMaterial::diffusePower() const
{
    return m_diffusePower;
}

void TblinnPhongMaterial::setDiffusePower(float diffusePower)
{
    m_diffusePower = diffusePower;
}









