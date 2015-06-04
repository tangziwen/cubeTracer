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

float TblinnPhongMaterial::BRDF(QVector3D viewDirection, QVector3D lightDirection, QVector3D normal)
{
    lightDirection = -lightDirection;
    auto half = (viewDirection + lightDirection).normalized();
    float specAngle =std::max(QVector3D::dotProduct (half, normal), 0.0f);
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









