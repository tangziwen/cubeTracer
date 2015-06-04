#ifndef TINTERSECTIONRESULT_H
#define TINTERSECTIONRESULT_H

#include "tvector.h"

class TbaseGeometry;

class TintersectionResult
{
public:
    TintersectionResult();
    ~TintersectionResult();
    Tvector pos() const;
    void setPos(const Tvector &pos);

    Tvector normal() const;
    void setNormal(const Tvector &normal);

    float distance() const;
    void setDistance(float distance);

    TbaseGeometry *geometry() const;
    void setGeometry(TbaseGeometry *geometry);

    static TintersectionResult getNotHit();
private:
    Tvector m_pos;
    Tvector m_normal;
    float m_distance;
    TbaseGeometry * m_geometry;
};

#endif // TINTERSECTIONRESULT_H
