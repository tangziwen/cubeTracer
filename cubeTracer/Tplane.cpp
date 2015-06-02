#include "Tplane.h"

Tplane::Tplane(QVector3D normal, float dist)
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
    auto a = QVector3D::dotProduct(ray.direction (),m_normal);
    if (a >= 0)
        return TintersectionResult::getNotHit ();

    auto b =QVector3D::dotProduct (m_normal,ray.origin () - m_pos);
    TintersectionResult result;
    result.setGeometry (this);
    result.setDistance (-b / a);
    result.setPos (ray.getPoint (result.distance ()));
    result.setNormal (m_normal);
    return result;
}

