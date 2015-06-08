#ifndef TPLANE_H
#define TPLANE_H

#include "TintersectionResult.h"
#include "TbaseGeometry.h"
#include "tvector.h"
class Tplane : public TbaseGeometry
{
public:
    Tplane(Tvector normal,float dist);
    ~Tplane();
    virtual TintersectionResult getIntersect(const Tray & ray);
    virtual GeometryType getType();
private:
    Tvector m_normal;
    Tvector m_pos;
    float m_dist;
};

#endif // TPLANE_H
