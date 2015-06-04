#include "TintersectionResult.h"

#include <TbaseGeometry.h>

TintersectionResult::TintersectionResult()
{

}

TintersectionResult::~TintersectionResult()
{

}
Tvector TintersectionResult::pos() const
{
    return m_pos;
}

void TintersectionResult::setPos(const Tvector &pos)
{
    m_pos = pos;
}
Tvector TintersectionResult::normal() const
{
    return m_normal;
}

void TintersectionResult::setNormal(const Tvector &normal)
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
    result.setPos (Tvector(0,0,0));
    result.setNormal (Tvector(0,0,0));
    return result;
}





