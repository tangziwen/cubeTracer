#include "Tray.h"

Tray::Tray(const QVector3D &orgin, const QVector3D &direction)
    :m_origin(orgin),m_direction(direction)
{
    m_direction.normalize ();
}

Tray::~Tray()
{

}
QVector3D Tray::origin() const
{
    return m_origin;
}

void Tray::setOrigin(const QVector3D &origin)
{
    m_origin = origin;
}
QVector3D Tray::direction() const
{
    return m_direction;
}

void Tray::setDirection(const QVector3D &direction)
{
    m_direction = direction;
    m_direction.normalize ();
}

QVector3D Tray::getPoint(float t) const
{
    auto f = m_direction;
    f *= t;
    return this->m_origin + f;
}



