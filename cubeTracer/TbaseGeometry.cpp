#include "TbaseGeometry.h"

TbaseGeometry::TbaseGeometry()
{
    m_material = NULL;
    m_isLight = false;
}

TbaseGeometry::~TbaseGeometry()
{

}
Tmaterial *TbaseGeometry::material() const
{
    return m_material;
}

void TbaseGeometry::setMaterial(Tmaterial *material)
{
    m_material = material;
}
bool TbaseGeometry::isLight() const
{
    return m_isLight;
}

void TbaseGeometry::setIsLight(bool isLight)
{
    m_isLight = isLight;
}



