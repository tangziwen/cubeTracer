#include "Tplane.h"

Tplane::Tplane(Tvector normal, float dist)
    :m_normal(normal),m_dist(dist)
{
    this->m_pos = m_normal;
    this->m_pos *= m_dist;
}

Tplane::~Tplane()
{

}

TintersectionResult Tplane::getIntersect(const Tray &ray)
{
    auto a = Tvector::dotProduct(ray.direction (),m_normal);
    if (a >= 0)
        return TintersectionResult::getNotHit ();

    auto b =Tvector::dotProduct (m_normal,ray.origin () - m_pos);
    TintersectionResult result;
    result.setGeometry (this);
    result.setDistance (-b / a);
    result.setPos (ray.getPoint (result.distance ()));
    result.setNormal (m_normal);
    return result;
}

TbaseGeometry::GeometryType Tplane::getType()
{
    return GeometryType::Plane;
}

