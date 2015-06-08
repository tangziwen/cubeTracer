#include "TbaseGeometry.h"

TbaseGeometry::TbaseGeometry()
{
    m_material = NULL;
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

TbaseGeometry::GeometryType TbaseGeometry::getType()
{
    return GeometryType::Undefined;
}



