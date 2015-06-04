#include "Tray.h"

Tray::Tray(const Tvector &orgin, const Tvector &direction)
    :m_origin(orgin),m_direction(direction)
{
    m_direction.normalize ();
}

Tray::~Tray()
{

}
Tvector Tray::origin() const
{
    return m_origin;
}

void Tray::setOrigin(const Tvector &origin)
{
    m_origin = origin;
}
Tvector Tray::direction() const
{
    return m_direction;
}

void Tray::setDirection(const Tvector &direction)
{
    m_direction = direction;
    m_direction.normalize ();
}

Tvector Tray::getPoint(float t) const
{
    auto f = m_direction;
    f *= t;
    return this->m_origin + f;
}



