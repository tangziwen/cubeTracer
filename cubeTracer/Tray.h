#ifndef TRAY_H
#define TRAY_H
#include "tvector.h"

class Tray
{
public:
    Tray(const Tvector &orgin, const Tvector & direction);
    ~Tray();
    Tvector origin() const;
    void setOrigin(const Tvector &origin);

    Tvector direction() const;
    void setDirection(const Tvector &direction);

    Tvector getPoint(float t) const;
private:
    Tvector m_origin;
    Tvector m_direction;
};

#endif // TRAY_H
