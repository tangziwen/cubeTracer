#include "TintersectionResult.h"

#include <TbaseGeometry.h>

TintersectionResult::TintersectionResult()
{

}

TintersectionResult::~TintersectionResult()
{

}
QVector3D TintersectionResult::pos() const
{
    return m_pos;
}

void TintersectionResult::setPos(const QVector3D &pos)
{
    m_pos = pos;
}
QVector3D TintersectionResult::normal() const
{
    return m_normal;
}

void TintersectionResult::setNormal(const QVector3D &normal)
{
    m_normal = normal;
}
float TintersectionResult::distance() const
{
    return m_distance;
}

void TintersectionResult::setDistance(float distance)
{
    m_distance = distance;
}
TbaseGeometry *TintersectionResult::geometry() const
{
    return m_geometry;
}

void TintersectionResult::setGeometry(TbaseGeometry *gometry)
{
    m_geometry = gometry;
}

TintersectionResult TintersectionResult::getNotHit()
{
    TintersectionResult result;
    result.setGeometry (NULL);
    result.setDistance (0);
    result.setPos (QVector3D(0,0,0));
    result.setNormal (QVector3D(0,0,0));
    return result;
}





