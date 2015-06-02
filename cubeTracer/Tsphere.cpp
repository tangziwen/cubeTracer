#include "Tsphere.h"
#include <math.h>
Tsphere::Tsphere(float radius, QVector3D center)
    :m_radius(radius),m_center(center)
{
    updateSqrRadius();
}

Tsphere::~Tsphere()
{

}
float Tsphere::radius() const
{
    return m_radius;
}

void Tsphere::setRadius(float radius)
{
    m_radius = radius;
    updateSqrRadius();
}
QVector3D Tsphere::center() const
{
    return m_center;
}

void Tsphere::setCenter(QVector3D cnter)
{
    m_center = cnter;
}

TintersectionResult Tsphere::getIntersect(const Tray &ray)
{

    auto v = ray.origin () - this->center ();
    auto a0 = v.lengthSquared () - this->m_sqrRadius;
    auto DdotV = QVector3D::dotProduct (ray.direction (),v);

    if (DdotV <= 0) {
        auto discr = DdotV * DdotV - a0;
        if (discr >= 0) {
            TintersectionResult result;
            result.setGeometry (this);
            result.setDistance (-DdotV - sqrt(discr));
            result.setPos (ray.getPoint(result.distance ()));
            auto normal = result.pos () - this->center ();
            normal.normalize ();
            result.setNormal (normal);
            return result;
        }
    }
    return TintersectionResult::getNotHit ();
}


void Tsphere::updateSqrRadius()
{
    m_sqrRadius = m_radius * m_radius;
}



